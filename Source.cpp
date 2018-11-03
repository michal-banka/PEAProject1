#include "Libs.h"
#include "Matrix.h"

int main()
{
	srand(time(nullptr));

	matrix graph("data.txt");
	graph.show();
	std::cout << "IS SYMETRIC? : " << (graph.isSymetric() ? "yes" : "no") << std::endl;
	graph.bruteForceInit();

	graph.branchAndBoundInit();
	std::cin.get();
	return 0;
}
