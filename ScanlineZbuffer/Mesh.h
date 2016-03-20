#pragma once
#include "armadillo"
using namespace std;
using namespace arma;


class Mesh
{
public:

	fmat v;
	icube f; // slice 0: vertex index, 1: normal index, 2:texture index
	fmat n;
	fmat t;

	Mesh();
	~Mesh();
};

