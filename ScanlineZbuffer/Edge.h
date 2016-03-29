#pragma once
#include "armadillo"
using namespace arma;
using namespace std;
class Edge
{
public:
	Edge();
	~Edge();
	bool Edge::operator<(const Edge &e) const;
	
	int ymax;
	
	float xi;
	float dx;

	float zi;
	float dz;

	fvec4 pi;
	fvec4 dp;

	fvec4 ni;
	fvec4 dn;

};

