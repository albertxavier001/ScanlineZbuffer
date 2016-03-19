#pragma once
#include "armadillo"
#include "Camera.h"
#include "Mesh.h"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;
using namespace arma;
class Scene
{
public:
	Mesh mesh;
	Camera cam;
public:
	Scene();
	~Scene();
	void loadScene(string fileName);
	void parseLine(const string &oneline);
};

