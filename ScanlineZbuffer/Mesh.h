#pragma once
#include "armadillo"
using namespace std;
using namespace arma;


class Mesh
{
public:

	fmat v;
	fcube f; // slice 0: v, 1: n, 2:t
	fmat n;
	fmat t;

	Mesh();
	~Mesh();
};

