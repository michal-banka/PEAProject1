#include "Libs.h"
#include "Matrix.h"
#include "Menu.h"

int main()
{
	srand(time(nullptr));

	//menu().mainMenu2();

	matrix matrix;
	matrix.changeSizeAndClear(10);
	for (int i = 0; i < 10; ++i)
	{
		matrix.fillVertexConnectionsRandom(i, 0, 20);
	}

	std::vector<int> min = matrix.geneticAlgorithmInit();
	std::vector<int> min2 = matrix.branchAndBoundInit();

	matrix.printCycle(min);
	matrix.printCycle(min2);
	std::cin.get();
	return 0;
}
