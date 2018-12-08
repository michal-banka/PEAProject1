#include "Libs.h"
#include "Matrix.h"
#include "Menu.h"

int main()
{
	srand(time(nullptr));

	//menu().mainMenu();
	matrix graph("data.txt");
	//graph.show();
	/*graph.addNVertex(15);
	for (int i = 0; i < graph.getVertices(); ++i)
	{
		graph.fillVertexConnectionsRandom(i, 0, 60);
	}
	graph.show();*/

	std::vector<int> minCycle = graph.simulatedAnnealingInit();
	graph.printCycle(minCycle);
	std::cout << graph.distance2(minCycle) << std::endl;

	/*std::vector<int> minCycle2 = graph.branchAndBoundInit();
	graph.printCycle(minCycle2);
	std::cout << graph.distance(minCycle2) << std::endl;*/

	std::cin.get();
	return 0;
}
