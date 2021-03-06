#pragma once
#include "Libs.h"
#include "SelectionMethodEnum.h"
#include "NeighbourhoodTypeEnum.h"
#include "TimeCounter.h"



class matrix
{
private:
	int** tab;
	int vertices;

	//functions needed to correct working of algorithms, used only in their bodies
	//Project1
	int lowerBound(std::vector<int> path);
	int upperBound();
	void branchAndBound(std::vector<int> cycle, int& upperBound, std::vector<int>& minCycle);
	void bruteForce(std::vector<int> cycle, int& minDist, std::vector<int>& minCycle);
	//Project2
	void simulatedAnnealing(std::vector<int> cycle, std::vector<int>& cycleMin, double tempStart, double tempMin, double stopTime, NeighbourhoodType neighbourhoodType);
	double getTemperatureStartAverage(int samplesSize);
	double getTemperatureStartMax(int samplesSize);
	

	//Project3
	std::vector<int> crossingHalfes(std::vector<int> parent1, std::vector<int> parent2);
	std::vector<int> mutationRandom(std::vector<int> parent, int levelsOfMutation);
	
public:
	matrix();
	matrix(int vertices, int** tab);
	matrix(int vertices);
	matrix(const matrix& m);
	matrix(std::string filename);
	~matrix();

	//matrix operations
	bool isSymetric();
	void changeSizeAndClear(int size);
	void show();
	void fillFromFile(std::string filename);

	//vertices operations
	int getVertices();
	int** getTab();
	int getElement(int x, int y);
	void addNVertex(int n);
	void addVertex();
	void removeVertex();
	void removeVertex(int n);
	void fillVertexConnections(int vertex);
	void fillVertexConnectionsRandom(int vertex, int rangeDown, int rangeUp);
	void fillVertexConnectionsRandomUnsymmetrical(int vertex, int rangeDown, int rangeUp);
	
	//vector operations
	std::vector<int> randomCycle();
	std::vector<int> getRandomTransformationOfVector(std::vector<int> vector, NeighbourhoodType type);
	void printCycle(std::vector<int> cycle);
	int distance(std::vector<int> vector);
	int distance2(std::vector<int> vector);

	//Project 1 algorithms
	std::vector<int> bruteForceInit();
	std::vector<int> branchAndBoundInit();
	std::vector<int> bruteForceInit(TimeCounter& counter);
	std::vector<int> branchAndBoundInit(TimeCounter& counter);

	//Project 2 algorithms
	std::vector<int> simulatedAnnealingInit(/*default neighbourhood type is SWAP*/);
	std::vector<int> simulatedAnnealingInit(NeighbourhoodType type, double maxTime, TimeCounter& counter);
	//std::vector<int> tabuSearch();

	//Project 3 algorithms
	std::vector<int> geneticAlgorithm();
	std::vector<int> geneticAlgorithm(int populationSize, int generations, double crossingProbability, double mutationProbability, double stopTime, SelectionMethod
	                                  selectionMethod, TimeCounter& counter);
	std::vector<int> geneticAlgorithm(int populationSize, int generations, double crossingProbability,
	                                  double mutationProbability, double stopTime, SelectionMethod selectionMethod);

	//others
	std::vector<int> randomSearch(int n);

	matrix& operator= (const matrix& m);
};
