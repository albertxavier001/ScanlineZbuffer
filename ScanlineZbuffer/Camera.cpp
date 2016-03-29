#include "Camera.h"


Camera::Camera()
	/*:eye(fvec4("0.0; 0.0; 1.0; 1.0")),
	 look(fvec4("0.0; 0.0; 0.0; 1.0")),
	 up(fvec4("0.0; 1.0; 0.0; 1.0")),
	 image(ivec2("640; 480")),
	 fov(45.0)*/
{
	eye.at(0) = 0.0f;
	eye.at(1) = 0.0f;
	eye.at(2) = 1.0f;
	eye.at(3) = 1.0f;

	look.at(0) = 0.0f;
	look.at(1) = 0.0f;
	look.at(2) = 0.0f;
	look.at(3) = 1.0f;

	up.at(0) = 0.0f;
	up.at(1) = 1.0f;
	up.at(2) = 0.0f;
	up.at(3) = 1.0f;

	image.at(0) = 640;
	image.at(1) = 480;

}


Camera::~Camera()
{
}

void Camera::rotX(const float &angleX) 
{

	eye.print("eye");
	look.print("look");

	fvec4 dir = eye - look;

	yDir = normalise(up);
	xDir = normalise(cross(dir, yDir));

	fmat::fixed<4, 4> R = hp.getXRotationMatrix(yDir, angleX);
	eye = look + R * dir;

	///xxx dump
	wcs2ccsMatrix = hp.getLookatMatrix(eye, look, up);
	ccs2viewMatrix = hp.perspectiveMatrix(fov, 0.001f, 300.f);
}

void Camera::rotY(const float &angleY)
{
	fvec4 dir = eye - look;
	yDir = normalise(up);
	xDir = normalise(cross(dir, yDir));
	
	fmat::fixed<4,4> R = hp.getXRotationMatrix(xDir, angleY);
	dir = R * dir;
	up = R * up;
	eye = look + dir;

	wcs2ccsMatrix = hp.getLookatMatrix(eye, look, up);
	ccs2viewMatrix = hp.perspectiveMatrix(fov, 0.001f, 300.f);
}

void Camera::scale(float s) 
{
	fvec dir = eye - look;
	dir *= s;
	eye = look + dir;
	wcs2ccsMatrix = hp.getLookatMatrix(eye, look, up);
	ccs2viewMatrix = hp.perspectiveMatrix(fov, 0.001f, 300.f);
}

void Camera::project(
	fvec4 &vin,
	fvec4 &vout)
{
	fvec4 v = wcs2ccsMatrix * vin;
	v = ccs2viewMatrix * v;
	v /= v.at(3);
	if (w < h)	v.at(1) *= (float)w / h;
	else		v.at(0) *= (float)h / w;
	vout.at(0) = (+v.at(0) + 1.f) / 2.f * w - 1.f;
	vout.at(1) = (-v.at(1) + 1.f) / 2.f * h - 1.f;
	vout.at(2) = v.at(2);
	vout.at(3) = 1;
}
