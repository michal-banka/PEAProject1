#pragma once
#include "Libs.h"
#include "TimeCounter.h"

class matrix
{
private:
	//Matrix will be always square
	int** tab;
	int vertices;

	int lowerBound(std::vector<int> path);
	int upperBound();
	void branchAndBound(std::vector<int> cycle, int& upperBound, std::vector<int>& minCycle);
	void bruteForce(std::vector<int> cycle, int& minDist, std::vector<int>& minCycle);
	
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
	bool isSymetric();
	void changeSizeAndClear(int size);

	void addNVertex(int n);
	void addVertex();
	void removeVertex();
	void removeVertex(int n);
	void fillVertexConnections(int vertex);
	void fillVertexConnectionsRandom(int vertex, int rangeDown, int rangeUp);
	void fillVertexConnectionsRandomUnsymmetrical(int vertex, int rangeDown, int rangeUp);
	int distance(std::vector<int> vector);

	void show();
	void fillFromFile(std::string filename);

	std::vector<int> bruteForceInit();
	std::vector<int> branchAndBoundInit();
	std::vector<int> bruteForceInit(TimeCounter& counter);
	std::vector<int> branchAndBoundInit(TimeCounter& counter);
	matrix& operator= (const matrix& m);
};
