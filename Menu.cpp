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

void menu::testsSA()
{
	TimeCounter timeCounter;
	std::vector<double> times(50);
	std::vector<int> results(50);


	//17 x 17 matrix
	graph.fillFromFile("17.txt");
	for(int i = 0 ; i < 50; i++)
	{
		results[i] = graph.distance(graph.simulatedAnnealingInit(SWAP,100, timeCounter));
		times[i] = timeCounter.getTime();
		system("cls");
		std::cout << "17 x 17 matrix - Simulated Annealing - SWAP - working ... [" << static_cast<double>(i / 50.0 * 100.0) << "% done]" << std::endl;
		
	}
	saveVectorToFile(times, "17_SWAP_TIMES");
	saveVectorToFile(results, "17_SWAP_RESULTS");

	for (int i = 0; i < 50; i++)
	{
		results[i] = graph.distance(graph.simulatedAnnealingInit(INSERT, 100, timeCounter));
		times[i] = timeCounter.getTime();
		system("cls");
		std::cout << "17 x 17 matrix - Simulated Annealing - INSERT - working ... [" << static_cast<double>(i / 50.0 * 100.0) << "% done]" << std::endl;
		
	}
	saveVectorToFile(times, "17_INSERT_TIMES");
	saveVectorToFile(results, "17_INSERT_RESULTS");

	for (int i = 0; i < 50; i++)
	{
		results[i] = graph.distance(graph.simulatedAnnealingInit(INVERT, 100, timeCounter));
		times[i] = timeCounter.getTime();
		system("cls");
		std::cout << "17 x 17 matrix - Simulated Annealing - INVERT - working ... [" << static_cast<double>(i / 50.0 * 100.0) << "% done]" << std::endl;
		
	}
	saveVectorToFile(times, "17_INVERT_TIMES");
	saveVectorToFile(results, "17_INVERT_RESULTS");

	//34 x 34 matrix
	graph.fillFromFile("34.txt");
	for (int i = 0; i < 50; i++)
	{
		results[i] = graph.distance(graph.simulatedAnnealingInit(SWAP, 100, timeCounter));
		times[i] = timeCounter.getTime();
		system("cls");
		std::cout << "34 x 34 matrix - Simulated Annealing - SWAP - working ... [" << static_cast<double>(i / 50.0 * 100.0) << "% done]" << std::endl;
		
	}
	saveVectorToFile(times, "34_SWAP_TIMES");
	saveVectorToFile(results, "34_SWAP_RESULTS");

	for (int i = 0; i < 50; i++)
	{
		results[i] = graph.distance(graph.simulatedAnnealingInit(INSERT, 100, timeCounter));
		times[i] = timeCounter.getTime();
		system("cls");
		std::cout << "34 x 34 matrix - Simulated Annealing - INSERT - working ... [" << static_cast<double>(i / 50.0 * 100.0) << "% done]" << std::endl;
		
	}
	saveVectorToFile(times, "34_INSERT_TIMES");
	saveVectorToFile(results, "34_INSERT_RESULTS");

	for (int i = 0; i < 50; i++)
	{
		results[i] = graph.distance(graph.simulatedAnnealingInit(INVERT, 100, timeCounter));
		times[i] = timeCounter.getTime();
		system("cls");
		std::cout << "34 x 34 matrix - Simulated Annealing - INVERT - working ... [" << static_cast<double>(i / 50.0 * 100.0) << "% done]" << std::endl;
		
	}
	saveVectorToFile(times, "34_INVERT_TIMES");
	saveVectorToFile(results, "34_INVERT_RESULTS");

	//56 x 56 matrix
	graph.fillFromFile("56.txt");
	for (int i = 0; i < 50; i++)
	{
		results[i] = graph.distance(graph.simulatedAnnealingInit(SWAP, 10000, timeCounter));
		times[i] = timeCounter.getTime();
		system("cls");
		std::cout << "56 x 56 matrix - Simulated Annealing - SWAP - working ... [" << static_cast<double>(i / 50.0 * 100.0) << "% done]" << std::endl;
		
	}
	saveVectorToFile(times, "56_SWAP_TIMES");
	saveVectorToFile(results, "56_SWAP_RESULTS");

	//70 x 70 matrix
	graph.fillFromFile("70.txt");
	for (int i = 0; i < 50; i++)
	{
		results[i] = graph.distance(graph.simulatedAnnealingInit(SWAP, 10000, timeCounter));
		times[i] = timeCounter.getTime();
		system("cls");
		std::cout << "70 x 70 matrix - Simulated Annealing - SWAP - working ... [" << static_cast<double>(i / 50.0 * 100.0) << "% done]" << std::endl;
		
	}
	saveVectorToFile(times, "70_SWAP_TIMES");
	saveVectorToFile(results, "70_SWAP_RESULTS");

	//171 x 171 matrix
	graph.fillFromFile("171.txt");
	for (int i = 0; i < 50; i++)
	{
		results[i] = graph.distance(graph.simulatedAnnealingInit(SWAP, 10000, timeCounter));
		times[i] = timeCounter.getTime();
		system("cls");
		std::cout << "171 x 171 matrix - Simulated Annealing - SWAP - working ... [" << static_cast<double>(i / 50.0 * 100.0) << "% done]" << std::endl;
		
	}
	saveVectorToFile(times, "171_SWAP_TIMES");
	saveVectorToFile(results, "171_SWAP_RESULTS");

	system("cls");
	std::cout << "171 x 171 matrix - Simulated Annealing - SWAP - working ... [100% done]" << std::endl;
}

void menu::mainMenu2()
{
	graph = matrix();

	int choice1 = 0;
	const int choices = 7;
	double time = 10.0;
	NeighbourhoodType type = SWAP;
	std::vector<int> minCycle;

	std::string filename;
	do
	{
		if (choice1 != 1 && choice1 <= 4) system("cls");
		std::cout << std::endl << "==== MAIN MENU ====" << std::endl;
		std::cout << "1. Show matrix " << std::endl;
		std::cout << "2. Create graph from file ..." << std::endl;
		std::cout << "3. Set time for stop criterion (now: "<< time  << ") ..." << std::endl;
		std::cout << "4. Neighbourhood type choice (now: "<< (type == NeighbourhoodType::SWAP ? "SWAP" :
														type == NeighbourhoodType::INSERT ? "INSERT" : "INVERT")  << ") ... " << std::endl;
		std::cout << "5. Run Simulated Annealing" << std::endl;
		std::cout << "6. Run tests" << std::endl;

		std::cout << choices << ". Quit." << std::endl;

		do
		{
			std::cout << "Your choice: ";
			std::cin >> choice1;
			std::cin.get();
			std::cout << std::endl;
		} while (choice1 <= 0 || choice1 > choices);

		switch (choice1)
		{
		case 1:
			graph.show();
			break;
		case 2:
			do
			{
				std::cout << "Insert filename with file type: ";
				std::cin >> filename;
				std::cin.get();
			} while (filename.empty());

			graph.fillFromFile(filename);
			break;
		case 3:
			do
			{
				std::cout << "Insert time in seconds: ";
				std::cin >> time;
				std::cin.get();
			} while (time <= 0.0);
			break;
		case 4:
			std::cout << "1. \"Swap\" type neighbourhood" << std::endl;
			std::cout << "2. \"Insert\" type neighbourhood" << std::endl;
			std::cout << "3. \"Invert\" type neighbourhood" << std::endl;
			std::cout << "4. Back ..." << std::endl;
			do
			{
				std::cout << "Insert number of type: ";
				std::cin >> choice1;
				std::cin.get();
			} while (choice1 <= 0 || choice1 > 4);

			if (choice1 == 1) type = SWAP;
			else if (choice1 == 2) type = INSERT;
			else if (choice1 == 3) type = INVERT;

			break;
		case 5:
			std::cout << "Calculating..." << std::endl;
			minCycle = graph.simulatedAnnealingInit();
			printCycle("Cycle - Sim. Annealing", minCycle);
			std::cout << "Distance of cycle: " << graph.distance(minCycle) << std::endl;;
			break;
		case 6:
			testsSA();
			break;
		default:
			break;
		}
	} while (choice1 != choices);
}

void menu::printCycle(std::string title, std::vector<int> cycle)
{
	if (cycle.empty()) return;

	std::cout << title << ": ";
	for (int element : cycle)
	{
		std::cout << element << " <-> ";
	}
	std::cout << cycle[0] << std::endl;
}

void menu::saveVectorToFile(std::vector<double> vector, std::string filename)
{
	std::string generatedFilesFolderPath = "results/";
	std::ofstream write;
	write.open(generatedFilesFolderPath + filename + ".txt");
	if (write.is_open())
	{
		for (double element : vector)
		{
			write << element << "\n";
		}
	}
	else
	{
		std::cout << "Error while opening file: " << generatedFilesFolderPath + filename + ".txt" << std::endl;
		std::cin.get();
	}
	write.close();
}

void menu::saveVectorToFile(std::vector<int> vector, std::string filename)
{
	std::string generatedFilesFolderPath = "results\\";
	std::ofstream write;
	write.open(generatedFilesFolderPath + filename + ".txt");
	if (write.is_open())
	{
		for (double element : vector)
		{
			write << element << "\n";
		}
	}
	else
	{
		std::cout << "Error while opening file: " << generatedFilesFolderPath + filename + ".txt" << std::endl;
		std::cin.get();
	}
	write.close();
}

void menu::mainMenu3()
{
	graph = matrix();

	TimeCounter counter;
	int choice1 = 0;
	const int choices = 11;
	double time = 10.0;
	int populationSize = 100;
	int generationsNumber = 100;
	double crossingProbability = 0.9;
	double mutationProbability = 0.1;
	SelectionMethod type = PROBABILITY;
	
	std::vector<int> minCycle;
	std::string filename;

	do
	{
		if (choice1 != 1 && choice1 < 9) system("cls");
		std::cout << std::endl << "==== MAIN MENU ====" << std::endl;
		std::cout << "1. Show matrix (" << (filename.empty() ? "empty" : filename) << ")" << std::endl;
		std::cout << "2. Create graph from file ..." << std::endl;
		std::cout << "3. Set time for stop criterion (now: " << time << ") ..." << std::endl;
		std::cout << "4. Selection type choice (now: " << (type == SelectionMethod::PROBABILITY ? "PROBABILITY" : "TOP") << ") ..." << std::endl;
		std::cout << "5. Set population size (now: " << populationSize <<") ..." << std::endl;
		std::cout << "6. Set generations number (now: " << generationsNumber << ") ..." << std::endl;
		std::cout << "7. Set crossing probability (now: " << crossingProbability << ") ..." << std::endl;
		std::cout << "8. Set mutation probability (now: " << mutationProbability << ") ..." << std::endl;
		std::cout << "9. Run Genetic Algorithm" << std::endl;
		std::cout << "10. Run tests" << std::endl;

		std::cout << choices << ". Quit." << std::endl;

		do
		{
			std::cout << "Your choice: ";
			std::cin >> choice1;
			std::cin.get();
			std::cout << std::endl;
		} while (choice1 <= 0 || choice1 > choices);

		switch (choice1)
		{
		case 1:
			graph.show();
			break;

		case 2:
			do
			{
				std::cout << "Insert filename with file type: ";
				std::cin >> filename;
				std::cin.get();
			} while (filename.empty());

			graph.fillFromFile(filename);
			break;

		case 3:
			do
			{
				std::cout << "Insert time in seconds: ";
				std::cin >> time;
				std::cin.get();
			} while (time <= 0.0);
			break;

		case 4:
			std::cout << "1. \"PROBABILITY\" selection type " << std::endl;
			std::cout << "2. \"TOP\" selection type" << std::endl;
			std::cout << "3. Back ..." << std::endl;
			do
			{
				std::cout << "Insert number of type: ";
				std::cin >> choice1;
				std::cin.get();
			} while (choice1 <= 0 || choice1 > 4);

			if (choice1 == 1) type = PROBABILITY;
			else if (choice1 == 2) type = TOP;
			system("cls");
			break;
		case 5:
			do
			{
				std::cout << "Insert population size: ";
				std::cin >> populationSize;
				std::cin.get();
			} while (populationSize <= 0);
			break;
			/*std::cout << "Calculating..." << std::endl;
			minCycle = graph.simulatedAnnealingInit();
			printCycle("Cycle - Sim. Annealing", minCycle);
			std::cout << "Distance of cycle: " << graph.distance(minCycle) << std::endl;;
			break;*/
		case 6:
			do
			{
				std::cout << "Insert generations number: ";
				std::cin >> generationsNumber;
				std::cin.get();
			} while (generationsNumber <= 0);
			break;
		case 7:
			std::cout << "Insert crossing probability: ";
			std::cin >> crossingProbability;
			std::cin.get();
			break;

		case 8:
			std::cout << "Insert mutation probability: ";
			std::cin >> mutationProbability;
			std::cin.get();
			break;

		case 9:
			minCycle = graph.geneticAlgorithm(populationSize,generationsNumber,crossingProbability,mutationProbability,time,type, counter);
			printCycle("Genetic algorithm",minCycle);
			std::cout << "Distance: " << graph.distance(minCycle) << std::endl;
			std::cout << "Time: " << counter.getTime() << std::endl;
			break;
		case 10:
			testsGA();
		default:
			break;
		}
	} while (choice1 != choices);
}

void menu::testsGA()
{
	TimeCounter timeCounter;
	std::vector<std::vector<double>> times(50 + 1);
	std::vector<std::vector<int>> results(50 + 1);
	int k = 0;
	//34 x 34 matrix
	graph.fillFromFile("34.txt");

	//PROB
	k = 0;
	for (int size = 50; size < 333; size += 50)
	{
		results[k].push_back(size);
		times[k].push_back(size);

		for (int i = 1; i < 51; i++)
		{
			results[k].push_back(graph.distance(graph.geneticAlgorithm(size,100,0.9,0.1,999,PROBABILITY, timeCounter)));
			times[k].push_back(timeCounter.getTime());
			system("cls");
			std::cout << "34 x 34 matrix - Genetic alg. - "<< size << " - PROBABILITY - working ... [" << static_cast<double>(i / 50.0 * 100.0) << "% done]" << std::endl;
		}
		k++;
	}
	saveVectorToFile(times, "34GRAPH_PROBABILITY_TIMES");
	saveVectorToFile(results, "34GRAPH_PROBABILITY_RESULTS");

	//TOP
	k = 0;
	for (int size = 50; size < 333; size += 50)
	{
		results[k].push_back(size);
		times[k].push_back(size);

		for (int i = 1; i < 51; i++)
		{
			results[k].push_back(graph.distance(graph.geneticAlgorithm(size, 100, 0.9, 0.1, 999, TOP, timeCounter)));
			times[k].push_back(timeCounter.getTime());
			system("cls");
			std::cout << "34 x 34 matrix - Genetic alg. - " << size << " - TOP - working ... [" << static_cast<double>(i / 50.0 * 100.0) << "% done]" << std::endl;
		}
		k++;
	}
	saveVectorToFile(times, "34GRAPH_TOP_TIMES");
	saveVectorToFile(results, "34GRAPH_TOP_RESULTS");



	//70 x 70 matrix
	graph.fillFromFile("70.txt");

	//PROB
	k = 0;
	for (int size = 50; size < 333; size += 50)
	{
		results[k].push_back(size);
		times[k].push_back(size);

		for (int i = 1; i < 51; i++)
		{
			results[k].push_back(graph.distance(graph.geneticAlgorithm(size, 100, 0.9, 0.1, 999, PROBABILITY, timeCounter)));
			times[k].push_back(timeCounter.getTime());
			system("cls");
			std::cout << "70 x 70 matrix - Genetic alg. - " << size << " - PROBABILITY - working ... [" << static_cast<double>(i / 50.0 * 100.0) << "% done]" << std::endl;
		}
		k++;
	}
	saveVectorToFile(times, "70GRAPH_PROBABILITY_TIMES");
	saveVectorToFile(results, "70GRAPH_PROBABILITY_RESULTS");

	//TOP
	k = 0;
	for (int size = 50; size < 333; size += 50)
	{
		results[k].push_back(size);
		times[k].push_back(size);

		for (int i = 1; i < 51; i++)
		{
			results[k].push_back(graph.distance(graph.geneticAlgorithm(size, 100, 0.9, 0.1, 999, TOP, timeCounter)));
			times[k].push_back(timeCounter.getTime());
			system("cls");
			std::cout << "70 x 70 matrix - Genetic alg. - " << size << " - TOP - working ... [" << static_cast<double>(i / 50.0 * 100.0) << "% done]" << std::endl;
		}
		k++;
	}
	saveVectorToFile(times, "70GRAPH_TOP_TIMES");
	saveVectorToFile(results, "70GRAPH_TOP_RESULTS");

	//171 x 171 matrix
	graph.fillFromFile("171.txt");
	//PROB
	k = 0;
	for (int size = 50; size < 333; size += 50)
	{
		results[k].push_back(size);
		times[k].push_back(size);

		for (int i = 1; i < 51; i++)
		{
			results[k].push_back(graph.distance(graph.geneticAlgorithm(size, 100, 0.9, 0.1, 999, PROBABILITY, timeCounter)));
			times[k].push_back(timeCounter.getTime());
			system("cls");
			std::cout << "171 x 171 matrix - Genetic alg. - " << size << " - PROBABILITY - working ... [" << static_cast<double>(i / 50.0 * 100.0) << "% done]" << std::endl;
		}
		k++;
	}
	saveVectorToFile(times, "171GRAPH_PROBABILITY_TIMES");
	saveVectorToFile(results, "171GRAPH_PROBABILITY_RESULTS");

	//TOP
	k = 0;
	for (int size = 50; size < 333; size += 50)
	{
		results[k].push_back(size);
		times[k].push_back(size);

		for (int i = 1; i < 51; i++)
		{
			results[k].push_back(graph.distance(graph.geneticAlgorithm(size, 100, 0.9, 0.1, 999, TOP, timeCounter)));
			times[k].push_back(timeCounter.getTime());
			system("cls");
			std::cout << "70 x 70 matrix - Genetic alg. - " << size << " - TOP - working ... [" << static_cast<double>(i / 50.0 * 100.0) << "% done]" << std::endl;
		}
		k++;
	}
	saveVectorToFile(times, "171GRAPH_TOP_TIMES");
	saveVectorToFile(results, "171GRAPH_TOP_RESULTS");

	system("cls");
	std::cout << "171 x 171 matrix - Genetic alg. - 300 - PROBABILITY - working ... [" << 100 << "% done]" << std::endl;

}

void menu::saveVectorToFile(std::vector<std::vector<int>> vector, std::string filename)
{
	std::string generatedFilesFolderPath = "results\\";
	std::ofstream write;
	write.open(generatedFilesFolderPath + filename + ".txt");
	if (write.is_open())
	{
		for (std::vector<int> element : vector)
		{
			for (int elementInt : element)
			{
				write << elementInt << " ";
			}
			write << std::endl;
		}
	}
	else
	{
		std::cout << "Error while opening file: " << generatedFilesFolderPath + filename + ".txt" << std::endl;
		std::cin.get();
	}
	write.close();
}

void menu::saveVectorToFile(std::vector<std::vector<double>> vector, std::string filename)
{
	std::string generatedFilesFolderPath = "results\\";
	std::ofstream write;
	write.open(generatedFilesFolderPath + filename + ".txt");
	if (write.is_open())
	{
		for (std::vector<double> element : vector)
		{
			for (int elementInt : element)
			{
				write << elementInt << " ";
			}
			write << std::endl;
		}
	}
	else
	{
		std::cout << "Error while opening file: " << generatedFilesFolderPath + filename + ".txt" << std::endl;
		std::cin.get();
	}
	write.close();
}
