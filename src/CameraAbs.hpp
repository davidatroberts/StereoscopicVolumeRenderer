#ifndef CAMERA_ABS
#define CAMERA_ABS

#include <string>

#include "Settings.hpp"

class CameraAbs {
public:
	CameraAbs() {

	}

	virtual ~CameraAbs() {

	}

	virtual void compute_uvw() = 0;
	virtual void render(bool thread) = 0;
	virtual void render_highlights(GraphSettings &graph_settings, 
		VolumeSettings &volume_settings, std::string image_side) = 0;
	virtual void output(std::string name) = 0;
};

#endif