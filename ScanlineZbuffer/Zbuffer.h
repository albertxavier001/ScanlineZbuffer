#pragma once
#include "Scene.h"
#include "QImage"
#include "armadillo"
#include "Edge.h"
#include "algorithm"
#include "Helper.h"
#include <cmath>
#include "Scene.h"
using namespace std;
using namespace arma;
class Zbuffer
{
public:
	Helper hp;
	Scene scene;

	Zbuffer();
	~Zbuffer();
	QImage ScanlineZbuffer(Scene &scene, const float &angleX, const float &angleY, const float & scale);
	void scan(Scene &scene, int ind, vector<float> &buffer, QImage &image);
	void initScanLineNewEdgeTable(vector< vector<Edge> > &slNet, fmat::fixed<4, 3> &v, fmat::fixed<4, 3> &vprj, fmat::fixed<4, 3> &nm, int ymin, int ymax);
	void ProcessScanLineFill(vector<vector<Edge>> &slNet, int ymin, int ymax, QImage &image, vector<float> &buffer, fvec4 &light);
};

