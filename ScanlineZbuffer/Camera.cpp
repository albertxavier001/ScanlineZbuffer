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
