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
	void simulatedAnnealing(std::vector<int> cycle, std::vector<int>& cycleMin, double tempStart, double tempMin, double stopTime);
	double getTemperatureStartAverage(int samplesSize);
	double getTemperatureStartMax(int samplesSize);
	double getTemperature(int iteration, double tempStart, double coolingSpeed);
	
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
	std::vector<int> randomCycle();
	std::vector<int> getRandomTransformationOfVector(std::vector<int> vector);
	void printCycle(std::vector<int> cycle);

	void addNVertex(int n);
	void addVertex();
	void removeVertex();
	void removeVertex(int n);
	void fillVertexConnections(int vertex);
	void fillVertexConnectionsRandom(int vertex, int rangeDown, int rangeUp);
	void fillVertexConnectionsRandomUnsymmetrical(int vertex, int rangeDown, int rangeUp);
	int distance(std::vector<int> vector);
	int distance2(std::vector<int> vector);

	void show();
	void fillFromFile(std::string filename);

	//Project 1
	std::vector<int> bruteForceInit();
	std::vector<int> branchAndBoundInit();
	std::vector<int> bruteForceInit(TimeCounter& counter);
	std::vector<int> branchAndBoundInit(TimeCounter& counter);

	//Project 2
	std::vector<int> simulatedAnnealingInit();
	std::vector<int> tabuSearch();

	matrix& operator= (const matrix& m);
};
