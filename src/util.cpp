#include "util.hpp"

void Util::assert_eq(bool eq, std::string message) {
	if (!eq) {
		std::cout << message << std::endl;
		exit(1);
	}
}

void Util::read_short_file_as_float(std::ifstream &file, float *data, 
	int size) {
	for (int i=0; i<size*2; i+=2) {
		unsigned char buf[2];
		file.read((char*)buf, 2);

		float val_f = byte_to_float(buf);

		int pos = i/2;
		data[pos] = val_f;
	}
}

void Util::circshift3d(Array::array3<std::complex<float>> &in, 
	Array::array3<std::complex<float>> &out, int xshift, int yshift, int zshift) {
	for (int i=0; i<in.Nx(); i++) {
		int ii = (i + xshift) % in.Nx();
		for (int j=0; j<in.Ny(); j++) {
			int jj = (j + yshift) % in.Ny();
			for (int k=0; k<in.Nz(); k++) {
				int kk = (k + zshift) % in.Nz();
				out(ii, jj, kk) = in(i, j, k);
			}
		}
	}
}

void Util::shift3d(Array::array3<std::complex<float>> &in, 
	Array::array3<std::complex<float>> &out) {
	circshift3d(in, out, in.Nx()/2, in.Ny()/2, in.Nz()/2);
}

int Util::round_to_int(double val) {
	return floor(val + 0.5);
}

bool Util::solve_quad(double a, double b, double c, double &t1, 
	double &t2) {
	double a_abs = 0;
	if (a >= 0.0) {
		a_abs = a;
	}
	else {
		a_abs = -a;
	}

	if (a_abs <= epsilon) {
		return false;
	}
	
	double disc = b*b - 4*a*c;
	if (disc < 0) {
		return false;
	} 
	else {
		double root = sqrt(disc);
		double tt1 = (-b + root) / (2.0 * a);
		double tt2 = (-b - root) / (2.0 * a);

		// determine if for all intents and purposes that they are the same
		double abs_diff = tt1 - tt2;
		if (abs_diff < 0) {
			abs_diff = -abs_diff;
		}
		if (abs_diff < epsilon) {
			return false;
		}

		// smallest root is first intersection point
		if (tt1 <= tt2) {
			return true;
		}
		else {
			double tmp = tt1;
			t1 = tt2;
			t2 = tmp;
			return true;
		}
	}
}

bool Util::near(double a, double b) {
	double diff = std::abs(a-b);
	if (diff <= epsilon) {
		return true;
	}
	return false;
}

bool Util::parse_json_array(std::string content, picojson::array& arr) {
	picojson::value v;
	std::string err;
	picojson::parse(v, content.c_str(), content.c_str() + strlen(content.c_str()), &err);
	if (!v.is<picojson::array>()) {
		return false;
	}

	arr= v.get<picojson::array>();
	return true;
}

bool Util::parse_json_array(picojson::value val, picojson::array& arr) {
	if (!val.is<picojson::array>()) {
		return false;
	}

	arr = val.get<picojson::array>();
	return true;
}

bool Util::parse_json_obj(picojson::value val, picojson::object& obj) {
	if (!val.is<picojson::object>()) {
		return false;
	}

	obj = val.get<picojson::object>();
	return true;
}

float Util::clamp(float x, float min, float max) {
		return (x < min ? min : (x > max ? max: x));
};

float Util::byte_to_float(unsigned char *buf) {
	unsigned short val = 0;
	val = (buf[1] << 8) | buf[0];

	float val_f = (float)val/(float)USHRT_MAX;
	return val_f;
}

double Util::compute_x_scale(double base_width, int vp_width) {
	return (double)(base_width / (double)vp_width);
}

double Util::compute_y_scale(double base_height, int vp_height) {
	return (double)(base_height / (double)vp_height);
}

double Util::compute_world_width(int vp_width, int vp_height, 
	double base_width, double base_height) {
	double x_scale = compute_x_scale(base_width, vp_width);

	double min_x = x_scale * (0.0 - 0.5 * ((double)vp_width - 1.0));
	double max_x = x_scale * (vp_width - 0.5 * ((double)vp_width - 1.0));

	return std::abs(min_x) + std::abs(max_x);
}

std::string Util::read_file(const char *filename, bool &parsed) {
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (in) {
		std::string contents;
	    in.seekg(0, std::ios::end);
	    contents.resize(in.tellg());
	    in.seekg(0, std::ios::beg);
	    in.read(&contents[0], contents.size());
	    in.close();
	    parsed = true;
	    return contents;
	}
	else {
		parsed = false;
		return "";
	}
};

double Util::epsilon = 0.001;