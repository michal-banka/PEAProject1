#include "Libs.h"
#include "Matrix.h"
#include "Menu.h"

int main()
{
	srand(time(nullptr));

	//menu().mainMenu();
	matrix graph("data.txt");
	//graph.addNVertex(10);
	/*for (int i = 0; i < graph.getVertices(); ++i)
	{
		graph.fillVertexConnectionsRandom(i, 1, 60);
	}*/
	graph.show();

	std::vector<int> minCycle = graph.simulatedAnnealingInit();
	graph.printCycle(minCycle);
	std::cout << graph.distance2(minCycle) << std::endl;

	std::vector<int> minCycle2 = graph.bruteForceInit();
	graph.printCycle(minCycle2);
	std::cout << graph.distance2(minCycle2) << std::endl;

	std::vector<int> minCycle3 = graph.branchAndBoundInit();
	graph.printCycle(minCycle3);
	std::cout << graph.distance2(minCycle3) << std::endl;

	std::cin.get();
	return 0;
}
