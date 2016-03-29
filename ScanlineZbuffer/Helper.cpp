#include "Helper.h"


Helper::Helper()
{
}


Helper::~Helper()
{
}

fmat::fixed<4, 4> Helper::getXRotationMatrix(const fvec4 &axis, const float &angle)
{
	fvec axisn = normalise(axis);
	struct VEC 
	{
		float x;
		float y;
		float z;
	};
	struct VEC v = 
	{
		axisn(0),
		axisn(1),
		axisn(2)
	};
	float c = cos(angle);
	float s = sin(angle);
	fmat R(4,4);
	int ind = 0;

	R[ind++] = c + (1 - c)*v.x*v.x;
	R[ind++] = (1 - c)*v.x*v.y + s*v.z;
	R[ind++] = (1 - c)*v.z*v.x - s*v.y;
	R[ind++] = 0;

	R[ind++] = (1 - c)*v.x*v.y - s*v.z;
	R[ind++] = c + (1 - c)*v.y*v.y;
	R[ind++] = (1 - c)*v.z*v.y + s*v.x;
	R[ind++] = 0;

	R[ind++] = (1 - c)*v.x*v.z + s*v.y;
	R[ind++] = (1 - c)*v.y*v.z - s*v.x;
	R[ind++] = c + (1 - c)*v.z*v.z;
	R[ind++] = 0;

	R[ind++] = 0;
	R[ind++] = 0;
	R[ind++] = 0;
	R[ind++] = 1;

	return R.t();

}

fmat::fixed<4,4> Helper::getLookatMatrix(const fvec4 eye, fvec4 look, fvec4 up) 
{
	fmat::fixed<4, 4> m;
	m.at(0, 3) = eye.at(0);
	m.at(1, 3) = eye.at(1);
	m.at(2, 3) = eye.at(2);
	m.at(3, 3) = 1.f;

	fvec3 _eye, _look, _up;

	_eye.at(0) = eye.at(0);
	_eye.at(1) = eye.at(1);
	_eye.at(2) = eye.at(2);

	_look.at(0) = look.at(0);
	_look.at(1) = look.at(1);
	_look.at(2) = look.at(2);

	_up.at(0) = up.at(0);
	_up.at(1) = up.at(1);
	_up.at(2) = up.at(2);

	fvec3 dir = normalise(_look - _eye);
	fvec3 yDir = normalise(_up);
	fvec3 _xDir = normalise(cross(yDir, dir));
	fvec3 upHat = cross(dir, _xDir);

	m.at(0, 0) = _xDir.at(0);
	m.at(1, 0) = _xDir.at(1);
	m.at(2, 0) = _xDir.at(2);
	m.at(3, 0) = 0.f;

	m.at(0, 1) = upHat.at(0);
	m.at(1, 1) = upHat.at(1);
	m.at(2, 1) = upHat.at(2);
	m.at(3, 1) = 0.f;

	m.at(0, 2) = dir.at(0);
	m.at(1, 2) = dir.at(1);
	m.at(2, 2) = dir.at(2);
	m.at(3, 2) = 0.f;

	return  m.i();

}

fmat::fixed<4, 4> Helper::perspectiveMatrix(const float &fov, const float & n, const float & f)
{
	fmat::fixed<4, 4> m;
	
	m.at(0, 0) = 1.f;
	m.at(1, 0) = 0.f;
	m.at(2, 0) = 0.f;
	m.at(3, 0) = 0.f;

	m.at(0, 1) = 0.f;
	m.at(1, 1) = 1.f;
	m.at(2, 1) = 0.f;
	m.at(3, 1) = 0.f;

	m.at(0, 2) = 0.f;
	m.at(1, 2) = 0.f;
	m.at(2, 2) = f/(f-n);
	m.at(3, 2) = -f*n/(f-n);

	m.at(0, 3) = 0.f;
	m.at(1, 3) = 0.f;
	m.at(2, 3) = 1.f;
	m.at(3, 3) = 0.f;


	float halfCotAngle = 1.f / tanf(fov * M_PI / 180.f / 2.f);
	fmat s = scaleMatrix(halfCotAngle, halfCotAngle, 1.f);
	///xxx order scale*pers or p0ers*scale
	return (m * s).t();
}


fmat::fixed<4, 4> Helper::scaleMatrix(const float &sx, const float & sy, const float & sz)
{
	fmat::fixed<4, 4> s(fill::zeros);
	s.at(0, 0) = sx;
	s.at(1, 1) = sy;
	s.at(2, 2) = sz;
	s.at(3, 3) = 1.f;
	return s;
}

int Helper::clamp(int value, int low, int up) {
	if (value > up)	return up;
	if (value < low) return low;
	return value;
}