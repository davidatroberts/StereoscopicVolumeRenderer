#ifndef PREMULTIPLIED_TRILINEAR
#define PREMULTIPLIED_TRILINEAR

#include "CCInterpolator.hpp"
#include "Vector4.hpp"

#define KERNEL_SIZE 5

class CCPremultipliedTrilinear: public CCInterpolator {
public:
	CCPremultipliedTrilinear(Vector min, Vector max);
	CCPremultipliedTrilinear(const CCPremultipliedTrilinear &other);

	~CCPremultipliedTrilinear();

	void preprocess(Matrix3D &mat);
	double interpolate(Vector &position, Matrix3D &mat);
	double reciprocal_sin2(double w);
	double pi_w(double w);

	friend void swap(CCPremultipliedTrilinear &first, 
		CCPremultipliedTrilinear &second);
	CCPremultipliedTrilinear& operator= (CCPremultipliedTrilinear other);

private:
	double min_r_range_;
	double max_r3_range_;
	double max_r_range_;
};

#endif