#pragma once
#include "armadillo"
#include "Helper.h"
#include <vector>
#include <string>
using namespace arma;
using namespace std;

class Camera
{
public:
	Camera();
	~Camera();
	void rotX(const float &angleX);
	void rotY(const float &angleY);
	void scale(float s);
	void project(fvec4 &vin, fvec4 &vout);
public:
	Helper hp;
	
	fvec4 eye;
	fvec4 look;
	fvec4 up;
	
	fvec4 xDir;
	fvec4 yDir;
	
	ivec2 image;
	float fov;
	
	fmat::fixed<4,4> wcs2ccsMatrix;
	fmat::fixed<4,4> ccs2viewMatrix;

	int w;
	int h;
};

