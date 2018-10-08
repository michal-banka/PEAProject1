#pragma once
#include "Libs.h"


class graph
{
private:
	std::vector<std::vector<int>> matrix;

public:
	graph();
	~graph();

	void setMatrix(std::vector<std::vector<int>> matrix);
	std::vector<std::vector<int>> getMatrix();
};

