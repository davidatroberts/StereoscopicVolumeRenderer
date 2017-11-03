#include "Settings.hpp"

#include <iomanip>

ViewSettings Settings::read_view_settings(
	picojson::value::object &json_obj) {
	ViewSettings settings;
	
	// get the camera type
	std::string camera_type = json_obj["camera"].to_str();
	if (camera_type.compare("mono")==0) {
		settings.camera = CameraType::MONO;
	}
	else if (camera_type.compare("stereo")==0) {
		settings.camera = CameraType::STEREO;
	}
	else if (camera_type.compare("anaglyph")==0) {
		settings.camera = CameraType::ANAGLYPH;
	}
	else if (camera_type.compare("colour_anaglyph")==0) {
		settings.camera = CameraType::COLOUR_ANAGLYPH;
	}
	else if (camera_type.compare("halfcolour_anaglyph")==0) {
		settings.camera = CameraType::HALFCOLOUR_ANAGLYPH;
	}
	else if (camera_type.compare("optimised_anaglyph")==0) {
		settings.camera = CameraType::OPTIMISED_ANAGLYPH;
	}
	else if (camera_type.compare("dubois_anaglyph")==0) {
		settings.camera = CameraType::DUBOIS_ANAGLYPH;
	}
	else if (camera_type.compare("cross_eye")==0) {
		settings.camera = CameraType::CROSS_EYE;
	}
	else {
		settings.camera = CameraType::UNKNOWN;
	}
	settings.camera_str = camera_type;

	settings.image_width = json_obj["width"].get<double>();
	settings.image_height = json_obj["height"].get<double>();
	settings.display_width_px = json_obj["display_width_px"].get<double>();

	settings.display_width_mm = json_obj["display_width_mm"].get<double>();
	settings.distance_to_display_mm 
		= json_obj["distance_to_display_mm"].get<double>();
	settings.IOD_mm = json_obj["IOD"].get<double>();


	settings.camera_axis = read_vector(json_obj["camera_axis"]);
	settings.camera_angle = json_obj["camera_angle"].get<double>();

	settings.background_colour = read_colour(json_obj["background_colour"]);

	settings.thread = json_obj["thread"].evaluate_as_boolean();

	// compute the other settings
	settings.world_width = Util::compute_world_width(
		settings.image_width, settings.image_height, BASE_WIDTH, BASE_HEIGHT);
	settings.image_width_mm = (settings.display_width_mm/
		(float)settings.display_width_px)*settings.image_width;
	settings.mm_to_world_ratio = settings.world_width / 
		settings.image_width_mm;
	settings.IOD_world = settings.mm_to_world_ratio * settings.IOD_mm;
	settings.distance_to_display_world = settings.distance_to_display_mm * 
		settings.mm_to_world_ratio;

	#ifdef VERBOSE
	print(settings);
	#endif

	return settings;
}

RaySettings Settings::read_ray_settings(
	picojson::value::object &json_obj) {
	RaySettings settings;

	settings.sub_sample = json_obj["sub_sample"].evaluate_as_boolean();
	settings.test_ray = json_obj["test_ray"].evaluate_as_boolean();

	settings.sample_step = json_obj["sample_step"].get<double>();
	settings.subsample_rate = json_obj["subsample_rate"].get<double>();

	#ifdef VERBOSE
	print(settings);
	#endif

	return settings;
}

VolumeSettings Settings::read_volume_settings(
	picojson::value::object &json_obj) {
	VolumeSettings settings;

	settings.volume_file = json_obj["file"].to_str();

	Vector resolution = read_vector(json_obj["resolution"]);
	settings.resolution = resolution;

	Vector ratio = read_vector(json_obj["ratio"]);
	settings.ratio = ratio;

	std::string lattice_type = json_obj["lattice_type"].to_str();
	if (lattice_type.compare("CC")==0) {
		settings.lattice = LatticeType::CC;
	}
	else if (lattice_type.compare("BCC")==0) {
		settings.lattice = LatticeType::BCC;
	}
	else if (lattice_type.compare("FCC")==0) {
		settings.lattice = LatticeType::FCC;
	}
	else {
		settings.lattice = LatticeType::UNKNOWN;
	}

	// check through the interpolation type, see if it's valid
	std::string interpolation_type = json_obj["interpolator"].to_str();
	if (interpolation_type.compare(0, lattice_type.size(), 
		lattice_type) != 0) {
		settings.interpolation = InterpolationType::INCORRECT_TYPE;
	}
	else {
		if (interpolation_type.compare("CC_trilinear")==0) {
			settings.interpolation = InterpolationType::CC_TRILINEAR;
		}
		else if (interpolation_type.compare("CC_catmull")==0) {
			settings.interpolation = InterpolationType::CC_CATMULL;
		}
		else if (interpolation_type.compare("CC_intbspline")==0) {
			settings.interpolation = InterpolationType::CC_INTBSPLINE;
		}
		else if (interpolation_type.compare("CC_bspline")==0) {
			settings.interpolation = InterpolationType::CC_BSPLINE;
		}
		else if (interpolation_type.compare("CC_pretrilinear")==0) {
			settings.interpolation = InterpolationType::CC_PRETRILINEAR;
		}
		else if (interpolation_type.compare("CC_windowsinc")==0) {
			settings.interpolation = InterpolationType::CC_WINDOWSINC;

			// get the radius of the window that will be used
			settings.window_radius 
				= (int)json_obj["window_radius"].get<double>();

			// get the window that will be used for the rendering
			std::string window_type = json_obj["window"].to_str();
			if (window_type.compare("rectangle")==0)
				settings.window = WindowType::RECTANGLE;
			else if (window_type.compare("bartlett")==0)
				settings.window = WindowType::BARTLETT;
			else if (window_type.compare("blackman")==0)
				settings.window = WindowType::BLACKMAN;
			else if (window_type.compare("cosine_bell")==0)
				settings.window = WindowType::COSINE_BELL;
			else if (window_type.compare("cosine_window")==0)
				settings.window = WindowType::COSINE_WINDOW;
			else if (window_type.compare("hamming")==0)
				settings.window = WindowType::HAMMING;
			else if(window_type.compare("hann")==0)
				settings.window = WindowType::HANN;
			else if (window_type.compare("lanczos")==0)
				settings.window = WindowType::LANCZOS;
			else if (window_type.compare("welch")==0)
				settings.window = WindowType::WELCH;
			else if (window_type.compare("kaiser")==0) {
				settings.window = WindowType::KAISER;
				double alpha = (double)json_obj["alpha"].get<double>();
				settings.interpolation_settings["alpha"] = alpha;
			}
			else
				settings.window = WindowType::UNKNOWN;

			settings.window_str = window_type;
		}
		else if(interpolation_type.compare("BCC_trilinear")==0) {
			settings.interpolation = InterpolationType::CC_TRILINEAR;
		}
		else if (interpolation_type.compare("FCC_trilinear")==0) {
			settings.interpolation = InterpolationType::CC_TRILINEAR;
		}
		else {
			settings.interpolation = InterpolationType::UNKNOWN;
		}
	}
	
	settings.interpolation_str = interpolation_type;
	settings.lattice_str = lattice_type;

	#ifdef VERBOSE
	print(settings);
	#endif

	return settings;
}

TransferSettings Settings::read_transfer_settings(
	picojson::value::object &json_obj) {
	TransferSettings settings;

	settings.red_file = json_obj["red"].to_str();
	settings.green_file = json_obj["green"].to_str();
	settings.blue_file = json_obj["blue"].to_str();
	settings.alpha_file = json_obj["alpha"].to_str();

	#ifdef VERBOSE
	print(settings);
	#endif

	return settings;
}

PointModifierSettings Settings::read_point_modifier_settings(
	picojson::value::object &json_obj) {
	PointModifierSettings settings;

	// check if there are any modifier parameters to use
	if (json_obj.find("point_modifier") == json_obj.end()) {
		return settings;
	}

	// check modifier is an array
	picojson::value mod_value = json_obj["point_modifier"];
	if (!mod_value.is<picojson::array>()) {
		return settings;
	}

	settings.parameters = mod_value.get<picojson::array>();

	#ifdef VERBOSE
	print(settings);
	#endif

	return settings;
}

CameraModifierSettings Settings::read_camera_modifier_settings(
	picojson::value::object &json_obj) {
	CameraModifierSettings settings;

	// check if there are any camera modifier parameters to use
	if (json_obj.find("camera_modifier") == json_obj.end()) {
		return settings;
	}

	// check that the modifier is an array
	picojson::value mod_value = json_obj["camera_modifier"];
	if (!mod_value.is<picojson::array>()) {
		return settings;
	}

	settings.parameters = mod_value.get<picojson::array>();

	return settings;
}

GraphSettings Settings::read_graph_settings(
	picojson::value::object &json_obj) {
	GraphSettings settings;
	// THIS IS REALLY UGLY CODE

	// check if there any camera modifiers to use
	if (json_obj.find("camera_modifier") == json_obj.end()) {
		return settings;
	}

	// check if the camera modifer settings are there
	picojson::value camera_value = json_obj["camera_modifier"];
	if (!camera_value.is<picojson::array>()) {
		return settings;
	}

	// loop through and see if the graph settings are there
	// only care about Highlight here, need to change this to make it 
	// be like PointModifier
	picojson::array modifiers = camera_value.get<picojson::array>();
	for (auto mod_value: modifiers) {
		picojson::value::object &mod_obj = mod_value.get<picojson::object>();

		std::string mod_type = mod_obj["type"].to_str();
		if (mod_type.compare("Highlight")==0) {
			bool active = mod_obj["active"].evaluate_as_boolean();
			if (!active)
				return settings;

			settings.highlight_nodes = true;

			// get the modifier settings object
			picojson::value graph_value = mod_obj["settings"];
			Util::assert_eq(graph_value.is<picojson::object>(),
				"Error in camera modifier definition");
			picojson::value::object &graph_obj 
				= graph_value.get<picojson::object>();

			// get the settings for the graph
			settings.sphere_radius = graph_obj["sphere_radius"].get<double>();
			settings.highlight_colour = {
				graph_obj["red"].get<double>(),
				graph_obj["green"].get<double>(),
				graph_obj["blue"].get<double>(),
				2255.0
			};

			// get the link files
			settings.link_file = graph_obj["link_file"].to_str();
			settings.no_link_file = graph_obj["no_link_file"].to_str();

			// parse all of the nodes 
			Settings::parse_node_list(settings);

			#ifdef VERBOSE
			print(settings);
			#endif
		}
		return settings;
	}

	return settings;
}

ShaderSettings Settings::read_shader_settings(
	picojson::value::object &json_obj) {
	ShaderSettings settings;

	// get the illumination model
	std::string illumination = json_obj["illumination_model"].to_str();
	if (illumination.compare("blinn_phong")==0) {
		settings.illumination_model = IlluminationModelType::BLINN_PHONG;
	}
	else {
		settings.illumination_model = IlluminationModelType::UNKNOWN;
	}

	// get the gradient function
	std::string gradient = json_obj["gradient_function"].to_str();
	if (gradient.compare("central_difference")==0) {
		settings.gradient = GradientType::CENTRAL_DIFFERENCE;
	}
	else {
		settings.gradient = GradientType::UNKNOWN;
	}

	// get the position and colour settings
	settings.light_position = read_vector(json_obj["light_position"]);
	settings.ka = read_vector(json_obj["ambient"]);
	settings.kd = read_vector(json_obj["diffuse"]);
	settings.ks = read_vector(json_obj["specular"]);
	settings.n = json_obj["shininess"].get<double>();
	settings.light_colour = read_vector(json_obj["light_colour"]);
	settings.ambient_colour = read_vector(json_obj["ambient_colour"]);

	// just set some strings
	settings.illumination_str = illumination;
	settings.gradient_str = gradient;

	#ifdef VERBOSE
	print(settings);
	#endif

	return settings;
}

Vector Settings::read_vector(picojson::value &json_val) {
	Util::assert_eq(json_val.is<picojson::object>(), "Error in reading vector");
	picojson::value::object &json_obj = json_val.get<picojson::object>();

	Vector v;
	v.x = json_obj["x"].get<double>();
	v.y = json_obj["y"].get<double>();
	v.z = json_obj["z"].get<double>();

	return v;
}

Colour Settings::read_colour(picojson::value &json_val) {
	Util::assert_eq(json_val.is<picojson::object>(), "Error in reading colour");
	picojson::value::object &json_obj = json_val.get<picojson::object>();

	Colour c;
	c.red = json_obj["r"].get<double>();
	c.green = json_obj["g"].get<double>();
	c.blue = json_obj["b"].get<double>();
	c.alpha = json_obj["a"].get<double>();

	return c;
}

void Settings::parse_node_list(GraphSettings &settings) {
	// attempt to open the file for the other json files
	bool parsed;
	std::string link_contents = Util::read_file(settings.link_file.c_str(),
		parsed);
	Util::assert_eq(parsed, "Failed to read LINK json contents");
	std::string no_link_contents = Util::read_file(
		settings.no_link_file.c_str(), parsed);
	Util::assert_eq(parsed, "Failed to read NO LINK json contents");

	// parse the json content
	picojson::array link_arr, no_link_arr;
	Util::assert_eq(Util::parse_json_array(link_contents, link_arr), 
		"Unable to parse LINK array");
	Util::assert_eq(Util::parse_json_array(no_link_contents, no_link_arr),
		"Unable to parse NO LINK array");

	for (unsigned int i=0; i<link_arr.size(); ++i) {
		picojson::value link_val = link_arr[i];
		picojson::value no_link_val = no_link_arr[i];

		picojson::array link_pair, no_link_pair;
		Util::assert_eq(Util::parse_json_array(link_val, link_pair),
			"Unable to parse pair");
		Util::assert_eq(Util::parse_json_array(no_link_val, no_link_pair),
			"Unable to parse no link pair");

		// link pairs
		picojson::object pos1, pos2;
		Util::assert_eq(Util::parse_json_obj(link_pair[0], pos1),
			"Unable to parse pos1");
		Util::assert_eq(Util::parse_json_obj(link_pair[1], pos2),
			"Unable to parse pos2");

		// no link pairs
		picojson::object pos3, pos4;
		Util::assert_eq(Util::parse_json_obj(no_link_pair[0], pos3),
			"Unable to parse pos3");
		Util::assert_eq(Util::parse_json_obj(no_link_pair[1], pos4),
			"Unable to parse pos4");

		// read through link values
		Vector n1pos1(
			pos1["x"].get<double>(), 
			pos1["y"].get<double>(),
			pos1["z"].get<double>());
		Vector n1pos2(
			pos2["x"].get<double>(),
			pos2["y"].get<double>(),
			pos2["z"].get<double>());
		Pair p1(Sphere(n1pos1, settings.sphere_radius), 
				Sphere(n1pos2, settings.sphere_radius), true);

		// read through nolink values
		Vector n2pos1(
			pos3["x"].get<double>(),
			pos3["y"].get<double>(),
			pos3["z"].get<double>());
		Vector n2pos2(
			pos4["x"].get<double>(),
			pos4["y"].get<double>(),
			pos4["z"].get<double>());
		Pair p2(Sphere(n2pos1, settings.sphere_radius), 
				Sphere(n2pos2, settings.sphere_radius), false);

		settings.pair_list.push_back(p1);
		settings.pair_list.push_back(p2);
	}
}


void Settings::print(ViewSettings &s) {
	std::cout << std::boolalpha;

	std::cout << "\033[1m" << "ViewSettings" << "\033[0m" << std::endl;
	std::cout << std::setw(27) << std::left<< "camera: " << s.camera_str 
		<< std::endl;
	std::cout << std::setw(27) << std::left << "thread"
		<< s.thread << std::endl;

	std::cout << std::setw(27) << std::left<< "image_width: " 
		<< s.image_width << std::endl;
	std::cout << std::setw(27) << std::left<< "image_height: " 
		<< s.image_height << std::endl;
	std::cout << std::setw(27) << std::left<< "display_width_px: " 
		<< s.display_width_px << std::endl;

	std::cout << std::setw(27) << std::left<< "display_width_mm: " 
		<< s.display_width_mm << std::endl;
	std::cout << std::setw(27) << std::left<< "distance_to_display_mm: " 
		<< s.distance_to_display_mm << std::endl;
	std::cout << std::setw(27) << std::left<< "IOD_mm: " << s.IOD_mm 
		<< std::endl;
	std::cout << std::setw(27) << std::left<< "camera_axis: " 
		<< s.camera_axis << std::endl;
	std::cout << std::setw(27) << std::left<< "camera_angle: " 
		<< s.camera_angle << std::endl;
	std::cout <<  std::setw(27) << std::left << "background_colour: "
		<< "(" << s.background_colour.red << ", "
	 	<< s.background_colour.green << ", " << s.background_colour.blue
	 	<< ")" << std::endl;

	std::cout << std::setw(27) << std::left<< "world_width: " 
		<< s.world_width << std::endl;
	std::cout << std::setw(27) << std::left<< "image_width_mm: " 
		<< s.image_width_mm << std::endl;
	std::cout << std::setw(27) << std::left<< "IOD_world: " << s.IOD_world 
		<< std::endl;
	std::cout << std::setw(27) << std::left<< "distance_to_display_world: " 
		<< s.distance_to_display_world << std::endl; 
	std::cout << std::endl;

	std::cout << std::noboolalpha;
}

void Settings::print(RaySettings &s) {
	std::cout << std::boolalpha;

	std::cout << "\033[1m" << "RaySettings" << "\033[0m" << std::endl;
	std::cout << std::setw(16) << std::left << "sub_sample: " 
		<< s.sub_sample << std::endl;
	std::cout << std::setw(16) << std::left << "test_ray: " 
		<< s.test_ray << std::endl;

	std::cout << std::setw(16) << std::left << "sample_step: " 
		<< s.sample_step << std::endl;
	std::cout << std::setw(16) << std::left << "subsample_rate: " 
		<< s.subsample_rate << std::endl;
	std::cout << std::endl;

	std::cout << std::noboolalpha;
}

void Settings::print(VolumeSettings &s) {
	std::cout << "\033[1m" << "VolumeSettings" << "\033[0m" << std::endl;
	std::cout << std::setw(22) << std::left << "volume_file: " 
		<< s.volume_file << std::endl; 

	std::cout << std::setw(22) << std::left << "resolution: " 
		<< s.resolution << std::endl;
	std::cout << std::setw(22) << std::left << "ratio: " << s.ratio 
		<< std::endl;
	std::cout << std::setw(22) << std::left << "lattice: " 
		<< s.lattice_str << std::endl;
	std::cout << std::setw(22) << std::left << "interpolation: " 
		<< s.interpolation_str << std::endl;

	// print off the windowsinc settings
	if (s.interpolation == InterpolationType::CC_WINDOWSINC) {
		std::cout << std::setw(22) << std::left << "window: " 
			<< s.window_str << std::endl;
		std::cout << std::setw(22) << std::left << "window_radius: "
			<< s.window_radius << std::endl;
	}

	std::cout << std::endl;
}

void Settings::print(GraphSettings &s) {
	std::cout << "\033[1m" << "GraphSettings" << "\033[0m" << std::endl;
	std::cout << std::setw(17) << std::left << "highlight_nodes: " 
		<< s.highlight_nodes << std::endl;
	std::cout << std::setw(17) << std::left << "sphere_radius: " 
		<< s.sphere_radius << std::endl;
	std::cout << std::setw(17) << std::left << "link_file: " 
		<< s.link_file << std::endl;
	std::cout << std::setw(17) << std::left << "no_link_file: " 
		<< s.no_link_file << std::endl;
	std::cout << std::endl;
}

void Settings::print(TransferSettings &settings) {
	std::cout << "\033[1m" << "TransferSettings" << "\033[0m" << std::endl;
	std::cout << "\033[31;40m" << std::setw(12) << std::left << "red_file: " 
		<< "\033[0m" << settings.red_file << std::endl;
	std::cout << "\033[32;40m" << std::setw(12) << std::left << "green_file: " 
		<< "\033[0m" << settings.green_file << std::endl;
	std::cout << "\033[34;40m" << std::setw(12) << std::left << "blue_file: " 
		<< "\033[0m" << settings.blue_file << std::endl;
	std::cout << std::setw(12) << std::left << "alpha_file: " 
		<< settings.alpha_file << std::endl;
	std::cout << std::endl;
}

void Settings::print(PointModifierSettings &settings) {
	std::cout << "\033[1m" << "PointModifierSettings" << "\033[0m" 
		<< std::endl;
	std::cout << "types: ";
	for (unsigned int i=0; i<settings.parameters.size(); ++i) {
		picojson::value mod_value = settings.parameters[i];
		picojson::value::object &mod_obj = mod_value.get<picojson::object>();

		std::string mod_type = mod_obj["type"].to_str();
		std::cout << mod_type << ", ";
	}
	std::cout << std::endl << std::endl;
}

void Settings::print(ShaderSettings &s) {
	std::cout << "\033[1m" << "ShadingSettings" << "\033[0m" << std::endl;
	std::cout << std::setw(16) << std::left << "illumination: " << 
		s.illumination_str << std::endl;
	std::cout << std::setw(16) << std::left << "gradient: " <<
		s.gradient_str << std::endl;
	std::cout << std::setw(16) << std::left << "light_position: " <<
		s.light_position << std::endl;
	std::cout << std::setw(16) << std::left << "ka: " << s.ka << std::endl;
	std::cout << std::setw(16) << std::left << "kd: " << s.kd << std::endl;
	std::cout << std::setw(16) << std::left << "ks: " << s.ks << std::endl;
	std::cout << std::setw(16) << std::left << "n: " << s.n << std::endl; 
	std::cout << std::setw(16) << std::left << "light_colour: " <<
		s.light_colour << std::endl;
	std::cout << std::setw(16) << std::left << "ambient_colour: " <<
		s.ambient_colour << std::endl;

	std::cout << std::endl;
}