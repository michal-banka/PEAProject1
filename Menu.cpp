#include "Menu.h"

menu::menu()
{
}


menu::~menu()
{
}

void menu::mainMenu()
{
	int choice1 = 0;
	int size = 0;
	std::string filename;
	do
	{
		std::cout << std::endl << "==== MAIN MENU ====" << std::endl;
		std::cout << "1. Create graph - from file ..." << std::endl;
		std::cout << "2. Create graph - given size, random values (symmetrical) ..." << std::endl;
		std::cout << "3. Create graph - given size, random values (unsymmetrical) ..." << std::endl;
		std::cout << "4. Create graph - given size, given values ..." << std::endl;
		std::cout << "5. Automatic time measurment - for documentation" << std::endl;
		std::cout << "6. Automatic time measurment - for documentation (only b&b)" << std::endl;
		std::cout << "7. Quit." << std::endl;

		do
		{
			std::cout << "Your choice: ";
			std::cin >> choice1;
			std::cin.get();
			std::cout << std::endl;
		} while (choice1 <= 0 || choice1 > 7);

		switch (choice1)
		{
		case 1:
			do
			{
				std::cout << "Insert filename with file type: ";
				std::cin >> filename;
				std::cin.get();
			} while (filename.empty());

			graph.fillFromFile(filename);
			graphMenu();
			break;
		case 2:
			do
			{
				std::cout << "Insert number of vertices: ";
				std::cin >> size;
				std::cin.get();
			} while (size <= 0 || size >= INT_MAX);

			graph.changeSizeAndClear(size);
			for (int i = 0; i < size; i++)
			{
				graph.fillVertexConnectionsRandom(i, 1, 25);
			}
			graphMenu();
			break;
		case 3:
			do
			{
				std::cout << "Insert number of vertices: ";
				std::cin >> size;
				std::cin.get();
			} while (size <= 0 || size >= INT_MAX);

			graph.changeSizeAndClear(size);
			for (int i = 0; i < size; i++)
			{
				graph.fillVertexConnectionsRandomUnsymmetrical(i, 1, 25);
			}
			graphMenu();
			break;
		case 4:
			do
			{
				std::cout << "Insert number of vertices: ";
				std::cin >> size;
				std::cin.get();
			} while (size <= 0 || size >= INT_MAX);

			graph.changeSizeAndClear(size);
			for (int i = 0; i < size; i++)
			{
				graph.fillVertexConnections(i);
			}
			graphMenu();
			break;
		case 5:
			tests();
			break;
		case 6:
			tests2();
			break;
		default:
			break;
		}
	} while (choice1 != 7);
}

void menu::graphMenu()
{
	int choice1 = 0;
	TimeCounter counter;
	std::vector<int> cycle;
	do
	{
		std::cout << std::endl << "==== GRAPH MENU ====" << std::endl;
		std::cout << "1. Add vertex ..." << std::endl;
		std::cout << "2. Delete vertex ..." << std::endl;
		std::cout << "3. Show matrix " << std::endl;
		std::cout << "4. Minimal Hamiltionian cycle - brute force" << std::endl;
		std::cout << "5. Minimal Hamiltionian cycle - branch and bound" << std::endl;
		std::cout << "6. Back." << std::endl;

		do
		{
			std::cout << "Your choice: ";
			std::cin >> choice1;
			std::cin.get();
			std::cout << std::endl;
		} while (choice1 <= 0 || choice1 > 6);
		switch (choice1)
		{
		case 1:
			graph.addVertex();
			graph.fillVertexConnections(graph.getVertices() - 1);
			break;

		case 2:
			graph.removeVertex();
			break;

		case 3:
			graph.show();
			break;

		case 4:
			if (graph.getVertices() > 10) std::cout << "This method might take long time for given size of matrix. " << std::endl;
			std::cout << "Computing . . . " << std::endl;

			cycle = graph.bruteForceInit(counter);

			std::cout << "=== Minimal Hamiltonian cycle for brute force method ===" << std::endl;
			for (int element : cycle)
			{
				std::cout << element << " <-> ";
			}
			std::cout << cycle[0] << std::endl;

			std::cout << "Weight of cycle: " << graph.distance(cycle) << std::endl;
			std::cout << "Time of calculating: " << counter.getTime() << " ms. " << std::endl;
			break;

		case 5:
			if (graph.getVertices() > 10) std::cout << "This method might take long time for given size of matrix. " << std::endl;
			std::cout << "Computing . . . " << std::endl;

			cycle = graph.branchAndBoundInit(counter);

			std::cout << "=== Minimal Hamiltonian cycle for Branch and Bound method ===" << std::endl;
			for (int element : cycle)
			{
				std::cout << element << " <-> ";
			}
			std::cout << cycle[0] << std::endl;

			std::cout << "Weight of cycle: " << graph.distance(cycle) << std::endl;
			std::cout << "Time of calculating: " << counter.getTime() << " ms. " << std::endl;
			break;

		default:
			break;
		}
	} while (choice1 != 6);
}

void menu::tests()
{
	std::vector<int> sizes = {8,9,10,11,12};
	std::vector<double> timesBruteForce(sizes.size(),0.0);
	std::vector<double> timesBB(sizes.size(), 0.0);
	TimeCounter counter;

	std::ofstream write;
	write.open("results.txt");
	if(write.is_open())
	{
		write << "size\tB&B\tBruteforce\n";
		for (int i = 0; i < sizes.size(); i++)
		{
			for (int j = 0; j < 100; ++j)
			{
				std::cout << "Graph size: " << sizes[i] << ", iteration: " << j << "/100" << std::endl;
				std::cout << "Graph generating... ";
				graph.changeSizeAndClear(sizes[i]);
				for (int k = 0; k < sizes[i]; k++)
				{
					graph.fillVertexConnectionsRandom(k, 1, 100);
				}
				std::cout << "DONE" << std::endl;

				std::cout << "B&B calculating... ";
				graph.branchAndBoundInit(counter);
				timesBB[i] += counter.getTime();
				std::cout << "DONE " << std::endl;
				std::cout << "Brute force calculating... ";
				graph.bruteForceInit(counter);
				timesBruteForce[i] += counter.getTime();
				std::cout << "DONE " << std::endl;
			}
			std::cout << std::endl;
			write << sizes[i] << "\t" << timesBB[i]/100.0 << "\t" << timesBruteForce[i]/100.0 << "\n";
		}

		std::cout << "== RESULTS (medium time, in ms.) ==" << std::endl;
		std::cout << "size\tB&B\tBruteforce\n";
		for(int i = 0 ; i < sizes.size(); i++)
		{
			std::cout << sizes[i] << "\t" << timesBB[i]/100.0 << "\t" << timesBruteForce[i]/100.0 << "\n";
		}
	}
	else
	{
		std::cout << "File has been not opened." << std::endl;
	}
	write.close();
}

void menu::tests2()
{
	std::vector<int> sizes = { 10,11,12,13,14,15,16,17,18,19,20 };
	std::vector<double> timesBB(sizes.size(), 0.0);
	TimeCounter counter;

	std::ofstream write;
	write.open("results2.txt");
	if (write.is_open())
	{
		write << "size\tB&B\n";
		for (int i = 0; i < sizes.size(); i++)
		{
			for (int j = 0; j < 100; ++j)
			{
				std::cout << "Graph size: " << sizes[i] << ", iteration: " << j << "/100" << std::endl;
				std::cout << "Graph generating... ";
				graph.changeSizeAndClear(sizes[i]);
				for (int k = 0; k < sizes[i]; k++)
				{
					graph.fillVertexConnectionsRandom(k, 1, 100);
				}
				std::cout << "DONE" << std::endl;

				std::cout << "B&B calculating... ";
				graph.branchAndBoundInit(counter);
				timesBB[i] += counter.getTime();
				std::cout << "DONE " << std::endl;
			}
			std::cout << std::endl;
			write << sizes[i] << "\t" << timesBB[i] / 100.0 << "\n";
		}

		std::cout << "== RESULTS (medium time, in ms.) ==" << std::endl;
		std::cout << "size\tB&B\n";
		for (int i = 0; i < sizes.size(); i++)
		{
			std::cout << sizes[i] << "\t" << timesBB[i] / 100.0  << "\n";
		}
	}
	else
	{
		std::cout << "File has been not opened." << std::endl;
	}
	write.close();
}
