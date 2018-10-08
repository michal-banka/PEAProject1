#include "Graph.h"



graph::graph()
{
}


graph::~graph()
{
}

void graph::setMatrix(std::vector<std::vector<int>> matrix)
{
	this->matrix = matrix;
}

std::vector<std::vector<int>> graph::getMatrix()
{
	return this->matrix;
}
