#include "Camera.h"


Camera::Camera()
	:eye(fvec("0.0; 0.0; 1.0")),
	 look(fvec("0.0; 0.0; 0.0")),
	 up(fvec("0.0; 1.0; 0.0")),
	 image(ivec("640; 480")),
	 fov(45.0)
{
}


Camera::~Camera()
{
}

void Camera::rotX(const float &angleX) {
	fvec dir = eye - look;
	yDir = normalise(up);
	xDir = normalise(cross(dir, yDir));

	fmat R = hp.getXRotationMatrix(yDir, angleX);
	eye = look + R * dir;

	///xxx dump
	wcs2ccsMatrix = hp.getLookatMatrix(eye, look, up);
	ccs2viewMatrix = hp.perspectiveMatrix(fov, 0.001f, 300.f);
}

void Camera::rotY(const float &angleY){
	fvec dir = eye - look;
	yDir = normalise(up);
	xDir = normalise(cross(dir, yDir));
	
	fmat R = hp.getXRotationMatrix(xDir, angleY);
	dir = R * dir;
	up = R * up;
	eye = look + dir;

	wcs2ccsMatrix = hp.getLookatMatrix(eye, look, up);
	ccs2viewMatrix = hp.perspectiveMatrix(fov, 0.001f, 300.f);
}

void Camera::scale(float s) {
	fvec dir = eye - look;
	dir *= s;
	eye = look + dir;
	wcs2ccsMatrix = hp.getLookatMatrix(eye, look, up);
	ccs2viewMatrix = hp.perspectiveMatrix(fov, 0.001f, 300.f);
}

