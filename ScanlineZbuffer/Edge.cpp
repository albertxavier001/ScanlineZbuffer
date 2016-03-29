#include "Edge.h"


Edge::Edge()
{
}


Edge::~Edge()
{
}
bool Edge::operator<(const Edge &e) const {
	return xi < e.xi;
}