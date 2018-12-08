#include "Libs.h"
#include "Matrix.h"
#include "Menu.h"

int main()
{
	srand(time(nullptr));

	//menu().mainMenu();

	std::cout << "=============== 17 (39) ====================" << std::endl;
	matrix graph("17.txt");

	std::vector<int> minCycle = graph.simulatedAnnealingInit();
	graph.printCycle(minCycle);
	std::cout << graph.distance2(minCycle) << std::endl;

	std::cout << "=============== 56 (1608) ====================" << std::endl;
	graph.fillFromFile("56.txt");

	minCycle = graph.simulatedAnnealingInit();
	graph.printCycle(minCycle);
	std::cout << graph.distance2(minCycle) << std::endl;

	std::cout << "=============== 70 (38673) ====================" << std::endl;
	graph.fillFromFile("70.txt");

	minCycle = graph.simulatedAnnealingInit();
	graph.printCycle(minCycle);
	std::cout << graph.distance2(minCycle) << std::endl;

	std::cout << "=============== 171 (2755) ====================" << std::endl;
	graph.fillFromFile("171.txt");

	minCycle = graph.simulatedAnnealingInit();
	graph.printCycle(minCycle);
	std::cout << graph.distance2(minCycle) << std::endl;

	std::cin.get();
	return 0;
}
