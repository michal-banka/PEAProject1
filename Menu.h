#pragma once
#include "Matrix.h"
#include "NeighbourhoodTypeEnum.h"
#include "SelectionMethodEnum.h"

class menu
{
private:
	matrix graph;
public:
	menu();
	~menu();

	//Project 1
	void mainMenu();
	void graphMenu();
	void tests();
	void tests2();

	//Project 2
	void testsSA();
	void mainMenu2();
	void printCycle(std::string title, std::vector<int> cycle);
	void saveVectorToFile(std::vector<double> vector, std::string filename);
	void saveVectorToFile(std::vector<int> vector, std::string filename);

	//Project 3
	void mainMenu3();
	void testsGA();
	void saveVectorToFile(std::vector<std::vector<int>> vector, std::string filename);
	void saveVectorToFile(std::vector<std::vector<double>> vector, std::string filename);
};

