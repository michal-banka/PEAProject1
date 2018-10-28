#include "Libs.h"
#include "Matrix.h"

int main()
{
	srand(time(nullptr));

	matrix graph;
	graph.addNVertex(4);
	for (int i = 0 ; i < 4 ;i++)
	{
		graph.fillVertexConnectionsRandom(i, 1, 15);
	}

	graph.show();
	std::vector<int> cycle;
	std::vector<int> cycleResult;
	graph.hamiltionianCycleBruteForce(cycle, cycleResult);

	graph.show();
	std::cout << "IS SYMETRIC? : " << graph.isSymetric();
	std::cin.get();
	return 0;
}
