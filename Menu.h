#pragma once
#include "Matrix.h"

class menu
{
private:
	matrix graph;
public:
	menu();
	~menu();

	void mainMenu();
	void graphMenu();
	void tests();
	void tests2();
};

