#pragma once
#include "Libs.h"
#include "Tree.h"
class matrix
{
private:
	int** tab;
	//Matrix will be always square, becouse this project represents only full graphs
	int vertices;

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
	std::vector<int> branchAndBound(Tree* parent);


	matrix& operator= (const matrix& m);
};