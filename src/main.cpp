#include <ctime>
#include <string>

#include "AABoundingBox.hpp"
#include "CameraAbs.hpp"
#include "CameraFactory.hpp"
#include "Caster.hpp"
#include "FrameBuffer.hpp"
#include "Interpolator.hpp"
#include "InterpolatorFactory.hpp"
#include "Lattice.hpp"
#include "LatticeFactory.hpp"
#include "PointModifierFactory.hpp"
#include "Quaternion.hpp"
#include "Settings.hpp"
#include "TransferFunction.hpp"
#include "Util.hpp"
#include "picojson.h"

#define BASE_SAMPLING_STEP 0.015625

int main(int argc, char *argv[]) {
	Util::assert_eq(argc >= 3, "Settings file or transfer function file missing");

	// get the required files first
	const auto input_file = std::string(argv[1]);
	const auto transfer_file = std::string(argv[2]);

	// see if a file name was entered (makes it easier for batch)
	std::string file_name;
	if (argc > 3) {
		file_name = std::string(argv[3]);
	}

	// attempt to read in file as JSON
	bool parsed = false;
	const auto json_contents = Util::read_file(input_file.c_str(), parsed);
	Util::assert_eq(parsed, "Failed to read JSON file");

	// read the json settings file
	picojson::value v;
	std::string err;
	picojson::parse(v, json_contents.c_str(), json_contents.c_str() + strlen(json_contents.c_str()), &err);

	// read the main object
	Util::assert_eq(v.is<picojson::object>(), "JSON is not an object");
	picojson::value::object &json_obj = v.get<picojson::object>();
	ViewSettings view_settings = Settings::read_view_settings(json_obj);
	RaySettings ray_settings = Settings::read_ray_settings(json_obj);

	// get the values only related to the volume
	picojson::value volume_value = json_obj["volume"];
	Util::assert_eq(volume_value.is<picojson::object>(), "Volume is not an object");
	picojson::value::object &volume_obj = volume_value.get<picojson::object>();
	VolumeSettings volume_settings = Settings::read_volume_settings(volume_obj);

	// get the values for the graph
	GraphSettings graph_settings = Settings::read_graph_settings(json_obj);

	// get settings for modifiers (if there are any)
	PointModifierSettings mod_settings = Settings::read_point_modifier_settings(json_obj);

	// get the values for the transfer function
	std::string transfer_contents = Util::read_file(transfer_file.c_str(), parsed);
	Util::assert_eq(parsed, "Failed to read transfer function JSON file");
	picojson::parse(v, transfer_contents.c_str(), transfer_contents.c_str() + strlen(transfer_contents.c_str()), &err);
	Util::assert_eq(v.is<picojson::object>(), "Transfer function JSON is not an object");
	picojson::value::object &transfer_json_obj = v.get<picojson::object>();
	TransferSettings transfer_settings = Settings::read_transfer_settings(transfer_json_obj);

	// make concrete interpolator
	InterpolatorFactory interpolator_factory(Vector(0, 0, 0), volume_settings.resolution);
	Interpolator *interpolator = interpolator_factory.make_interpolator(volume_settings);
	Util::assert_eq(interpolator != NULL, "Unknown interpolator used");

	// rotate the scaling and ensure all are > 0
	Quaternion rotate_q = Quaternion::create_rotation(view_settings.camera_axis, view_settings.camera_angle);
	if (!(volume_settings.ratio.x == 1 && volume_settings.ratio.y == 1 && volume_settings.ratio.z == 1)) {
		volume_settings.ratio = rotate_q.rotate_vector(volume_settings.ratio);
		volume_settings.ratio =
			Vector(fabs(volume_settings.ratio.x), fabs(volume_settings.ratio.y), fabs(volume_settings.ratio.z));
	}

	// make concrete lattice
	Vector min_cube_coord(0, 0, 0);
	LatticeFactory lattice_factory(min_cube_coord, volume_settings.ratio, volume_settings.resolution, interpolator);
	Lattice *lattice = lattice_factory.make_lattice(volume_settings.lattice);
	Util::assert_eq(lattice != NULL, "Unknown lattice used");
	Util::assert_eq(lattice->load(volume_settings.volume_file), "Failed to load the lattice properly");

	// run any preprocessing required for the lattice and filter
	Util::assert_eq(lattice->preprocess(), "Failed to preprocess the lattice");
	interpolator->preprocess(lattice->raw_data());

	// setup bounding box
	Vector bboxmin(-120 * volume_settings.ratio.x, -120 * volume_settings.ratio.y, 120 * volume_settings.ratio.z);
	Vector bboxmax(120 * volume_settings.ratio.x, 120 * volume_settings.ratio.y, -120 * volume_settings.ratio.z);
	AABoundingBox bounding_box(bboxmin, bboxmax, lattice);

	// create and load transfer function
	TransferFunction transfer_function(BASE_SAMPLING_STEP);
	Util::assert_eq(
		transfer_function.map_transfer_function(
			transfer_settings.red_file, transfer_settings.green_file, transfer_settings.blue_file,
			transfer_settings.alpha_file),
		"Failed to read in transfer file properly");
	transfer_function.adapt_with_sampling(ray_settings.sample_step);

	// setup any point modifiers that have been defined
	PointModifierFactory point_mod_factory;
	PointModifier *modifier = point_mod_factory.make_modifier(mod_settings, ray_settings, volume_settings);

	// create the raycaster
	Caster *caster = new Caster(
		&bounding_box, &transfer_function, modifier, ray_settings.sample_step, view_settings.background_colour);

	// setup camera
	Vector eye(0.0, 0.0, view_settings.distance_to_display_world);
	eye = rotate_q.rotate_vector(eye);
	Vector lookat(0.0, 0.0, 0.0);
	Vector up(0.0, 1.0, 0.0);
	up = rotate_q.rotate_vector(up);

	// create the camera that will be used to produce images
	CameraFactory camera_factory(eye, lookat, up, caster, ray_settings);
	CameraAbs *camera = camera_factory.make_camera(view_settings);
	Util::assert_eq(camera != NULL, "Unknown camera used");

	clock_t start = clock();

	// PERFORM RAYCASTING
	camera->render(view_settings.thread);
	camera->output(file_name);
	camera->render_highlights(graph_settings, volume_settings, "");
	// END RAYCASTING

	clock_t end = clock();
	clock_t duration = end - start;
	float duration_sec((float)duration / CLOCKS_PER_SEC);

	std::cout << "Finished raycaster" << std::endl;
	std::cout << "Took: " << duration_sec << " seconds" << std::endl;
}
