#pragma once
#include "Libs.h"
class Matrix
{
private:
	int** tab;
	int vertices;
public:
	Matrix();
	//Matrix will be always square, becouse this will represent full graph and this is the most efficent
	Matrix(int vertices);
	Matrix(const Matrix& m);
	Matrix(std::string filename);
	~Matrix();

	int getVertices();
	//void setTab(int** tab);
	//void setVertices(int vertices);

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

	Matrix& operator= (const Matrix& m);
};