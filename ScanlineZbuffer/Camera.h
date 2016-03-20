#pragma once
#include "armadillo"
#include <vector>
#include <string>
using namespace arma;
using namespace std;

class Camera
{
public:
	Camera();
	~Camera();

public:
	fvec eye;
	fvec look;
	fvec up;
	ivec image;
	float fov;
};

