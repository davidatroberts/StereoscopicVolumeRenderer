#ifndef WINDOW_SINC_INTERPOLATOR
#define WINDOW_SINC_INTERPOLATOR

#include "cc_interpolator.hpp"

/*
 * Implementation is based on the ITK windowed sinc code
 */
class CCWindowSinc : public CCInterpolator {
public:
	CCWindowSinc(Vector min, Vector max, int radius, std::function<double(double)> window_func);

	~CCWindowSinc();

	void preprocess(Matrix3D &mat);
	double interpolate(const Vector &position, const Matrix3D &mat) const;
	inline double sinc(double x) const {
		double px = M_PI * x;
		return (x == 0.0) ? 1.0 : std::sin(px) / px;
	}

private:
	int radius_;
	int window_m_;
	std::function<double(double)> window_func_;
};

#endif
