#include "Libs.h"
#include "Matrix.h"
#include "Menu.h"
#include "SelectionMethodEnum.h"

int main()
{
	srand(time(nullptr));

	menu().mainMenu3();

	/*matrix matrix("56.txt");
	
	matrix.show();

	int dist1 = 0, dist2 = 0, dist3 = 0;

	for (int i = 0; i < 20; ++i)
	{
		std::vector<int> min = matrix.geneticAlgorithm(50, 200, 0.9, 0.1, 10, SelectionMethod::TOP);
		dist1 += matrix.distance(min);
		matrix.printCycle(min);

		std::vector<int> min2 = matrix.geneticAlgorithm(50, 200, 0.9, 0.1, 10, SelectionMethod::PROBABILITY);
		dist2 += matrix.distance(min2);
		matrix.printCycle(min2);

		std::vector<int> min3 = matrix.randomSearch(1);
		dist3 += matrix.distance(min3);
		matrix.printCycle(min3);

		std::cout << i << ". ==========================================  " << std::endl;
	}

	std::cout << "#1: " << dist1 / 20 << std::endl;
	std::cout << "#2: " << dist2 / 20 << std::endl;
	std::cout << "#3: " << dist3 / 20 << std::endl;*/
	
	std::cin.get();
	return 0;
}
