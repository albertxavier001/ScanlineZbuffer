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
public:
	Helper hp;
	
	fvec eye;
	fvec look;
	fvec up;
	
	fvec xDir;
	fvec yDir;
	
	ivec image;
	float fov;
	
	fmat wcs2ccsMatrix;
	fmat ccs2viewMatrix;

};

