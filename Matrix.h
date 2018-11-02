#pragma once
#include "Libs.h"
#include "Tree.h"
class matrix
{
private:
	//Matrix will be always square
	int** tab;
	int vertices;

	int lowerBound(std::vector<int> path);
	std::vector<int> hamiltionianCycleBruteForce(std::vector<int> cycle, int& minDist, std::vector<int> minCycle);

public:
	matrix();
	matrix(int vertices, int** tab);
	matrix(int vertices);
	matrix(const matrix& m);
	matrix(std::string filename);
	~matrix();

	int getVertices();
	int** getTab();
	int getElement(int x, int y);
	//void setTab(int** tab);
	//void setVertices(int vertices);
	bool isSymetric();

	void addNVertex(int n);
	void addVertex();
	void removeVertex();
	void removeVertex(int n);
	void fillVertexConnections(int vertex);
	void fillVertexConnectionsRandom(int vertex, int rangeDown, int rangeUp);

	void show();

	std::vector<int> hamiltionianCycleBruteForceInit();
	std::vector<int> branchAndBound(std::vector<int> cycle, int& minDist, std::vector<int> minCycle);


	matrix& operator= (const matrix& m);
};