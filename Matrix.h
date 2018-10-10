#pragma once
#include "Libs.h"
class matrix
{
private:
	int** tab;
	int vertices;
public:
	matrix();
	//Matrix will be always square, becouse this will represent full graph
	matrix(int vertices);
	matrix(const matrix& m);
	matrix(std::string filename);
	~matrix();

	int getVertices();
	//void setTab(int** tab);
	//void setVertices(int vertices);
	bool isSymetric();

	void addNVertex(int n);
	void addVertex();
	void removeVertex();
	void removeVertex(int n);
	void fillVertexConnections(int vertex);

	void show();

	//int dijkstra(int from, int to, bool directed);
	//int prim(int from);
	//int prim2(int from);
	//int kruskal();
	//int bellman_ford(int from, int to, bool directed);

	matrix& operator= (const matrix& m);
};