#include "CCTrilinear.hpp"

CCTrilinear::CCTrilinear(Vector min, Vector max): CCInterpolator(min, max) {

}

CCTrilinear::~CCTrilinear() {

}

void CCTrilinear::preprocess(Matrix3D &mat) {
	
}

double CCTrilinear::interpolate(Vector &position, Matrix3D &mat) {
	int i = (unsigned int)position.x;
	int j = (unsigned int)position.y;
	int k = (unsigned int)position.z;

	float bx = position.x - (float)i;
	float by = position.y - (float)j;
	float bz = position.z - (float)k;

	return (mat(i, j, k) 	   * (1.0f-bx) * (1.0f-by) * (1.0f-bz) +
      		mat(i+1, j, k)     *  bx    * (1.0f-by) * (1.0f-bz) +
      		mat(i+1, j+1, k)   *  bx    *  by    * (1.0f-bz) +
      		mat(i, j+1, k) 	   * (1.0f-bx) *  by    * (1.0f-bz) +
      		mat(i, j, k+1)     * (1.0f-bx) * (1.0f-by) *  bz    +
      		mat(i+1, j, k+1)   *  bx    * (1.0f-by) *  bz    +
      		mat(i+1, j+1, k+1) *  bx    *  by    *  bz    +
      		mat(i, j+1, k+1)   * (1.0f-bx) *  by    *  bz);
}