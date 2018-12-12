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
	//Project 1
	void tests();
	void tests2();
	//Project 2
	void testsSA();
	void mainMenu2();
	void printCycle(std::string title, std::vector<int> cycle);
	void saveVectorToFile(std::vector<double> vector, std::string filename);
};

