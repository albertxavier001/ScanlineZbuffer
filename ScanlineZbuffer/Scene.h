#pragma once
#include "armadillo"
#include "Camera.h"
#include "Mesh.h"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Helper.h"
using namespace std;
using namespace arma;
class Scene
{
public:
	Mesh mesh;
	Camera cam;
	fvec4 light;
	Helper hp;
public:
	Scene();
	~Scene();
	void loadScene(string fileName);
	void parseLine(const string &oneline);
	void assignNormal();
};

