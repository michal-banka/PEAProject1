#include "Libs.h"
#include "Matrix.h"

int main()
{
	srand(time(nullptr));

	matrix graph("data.txt");
	//graph.hamiltionianCycleBruteForce(cycle, cycleResult);

	graph.show();
	std::cout << "IS SYMETRIC? : " << graph.isSymetric();
	std::cin.get();
	return 0;
}
