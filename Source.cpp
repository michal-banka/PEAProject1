#include "Libs.h"
#include "Matrix.h"
#include "Table.h"

int main()
{
	srand(time(nullptr));

	matrix graph("data.txt");
	graph.show();
	std::cout << "IS SYMETRIC? : " << (graph.isSymetric() ? "yes" : "no") << std::endl;
	graph.hamiltionianCycleBruteForceInit();
	std::cin.get();
	return 0;
}
