#include "Libs.h"
#include "Matrix.h"
#include "Menu.h"
#include "SelectionMethodEnum.h"

int main()
{
	srand(time(nullptr));

	//menu().mainMenu2();

	matrix matrix;
	matrix.changeSizeAndClear(150);
	for (int i = 0; i < 150; ++i)
	{
		matrix.fillVertexConnectionsRandom(i, 0, 20);
	}
	matrix.show();
	for (int i = 0; i < 20; ++i)
	{
		std::vector<int> min = matrix.geneticAlgorithm(50, 999, 0.1, 0.9, 10, SelectionMethod::TOP);
		matrix.printCycle(min);
		std::vector<int> min2 = matrix.geneticAlgorithm(50, 999, 0.1, 0.9, 10, SelectionMethod::PROBABILITY);
		matrix.printCycle(min2);
		//std::vector<int> min3 = matrix.branchAndBoundInit();
		//matrix.printCycle(min3);
		std::cout << " ==========================================  " << std::endl;
	}
	
	std::cin.get();
	return 0;
}
