#include "Libs.h"
#include "Matrix.h"
#include "Menu.h"

int main()
{
	srand(time(nullptr));

	//menu().mainMenu();
	matrix graph;
	graph.addNVertex(11);
	for (int i = 0; i < graph.getVertices(); ++i)
	{
		graph.fillVertexConnectionsRandom(i, 0, 60);
	}
	
	std::vector<int> minCycle = graph.simulatedAnnealingInit();
	graph.printCycle(minCycle);
	std::cout << graph.distance(minCycle);

	std::vector<int> minCycle2 = graph.bruteForceInit();
	graph.printCycle(minCycle2);
	std::cout << graph.distance(minCycle2);

	std::cin.get();
	return 0;
}
