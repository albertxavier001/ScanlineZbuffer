#pragma once
#define _USE_MATH_DEFINES
#include "armadillo"
#include <vector>
#include <ctime>

using namespace std;
using namespace arma;

class Helper
{
public:
	Helper();
	~Helper();

	fmat::fixed<4, 4> getXRotationMatrix(const fvec4 &axis, const float &angle);
	fmat::fixed<4, 4> getLookatMatrix(const fvec4 eye, fvec4 look, fvec4 up);
	fmat::fixed<4, 4> perspectiveMatrix(const float &fov, const float & n, const float & f);
	fmat::fixed<4, 4> scaleMatrix(const float &sx, const float & sy, const float & sz);
	int clamp(int value, int low, int up);
};

