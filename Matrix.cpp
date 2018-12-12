#include "Matrix.h"


matrix::matrix()
{
	this->vertices = 0;
	this->tab = nullptr;
}

matrix::matrix(int vertices, int** tab)
{
	this->vertices = vertices;
	this->tab = tab;
}

matrix::matrix(int vertices)
{
	this->vertices = vertices;
	this->tab = new int*[vertices];
	for (int i = 0 ; i < vertices; i++)
	{
		this->tab[i] = new int[vertices];
		for(int j = 0 ; j < vertices; j++)
		{
			tab[i][j] = 0;
		}
	}
}

matrix::matrix(const matrix& m)
{
	this->vertices = m.vertices;

	this->tab = new int*[vertices];
	for (int i = 0; i < vertices; i++)
	{
		this->tab[i] = new int[vertices];
	}

	for (int i = 0; i < vertices; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			this->tab[i][j] = m.tab[i][j];
		}
	}

}

matrix::matrix(std::string filename)
{
	this->vertices = 0;
	this->tab = nullptr;
	int i = 0, j = 0;
	int value = 0;
	int size = 0;
	std::ifstream read;
	read.open(filename);
	if (read.is_open())
	{
		read >> size;

		if (!read.fail())
		{
			this->vertices = size;

			//init tab with 0
			tab = new int*[vertices];
			for (int i = 0 ; i < vertices; i++)
			{
				tab[i] = new int[vertices];
				for (int j = 0; j < vertices; j++)
				{
					tab[i][j] = 0;
				}
			}

			//get values from file
			for (int k = 0; k < vertices * vertices; k++)
			{
				read >> value;
				if (!read.fail())
				{
					this->tab[i][j] = value;
					if (++j > vertices - 1)
					{
						j = 0;
						if (++i > vertices - 1)
						{
							break;
						}
					}
				}
				else
				{
					std::cout << "Read VALUE from file error." << std::endl;
					break;
				}
			}
		}
		else
		{
			std::cout << "Read SIZE from file error." << std::endl;
		}
	}
	else
	{
		std::cout << "File has NOT been opened correctly." << std::endl;
	}
}

matrix::~matrix()
{
	for (int i = 0; i < vertices; i++)
	{
		delete[] tab[i];
	}
	delete[] tab;
}

int matrix::lowerBound(std::vector<int> path)
{
	//if cycle == 0 we can't predict correctly
	if (path.empty()) return INT_MAX;

	int lb = 0;
	int minimum = INT_MAX;
	int minimum2 = INT_MAX;
	//add lengths of existing paths
	for (int i = 0 ; i < path.size() - 1; i++)
	{
		lb += tab[path[i]][path[i + 1]];
	}

	//add the smallest possible edge to bound
	//possible are only not used vertices (and beggining vertex if we aren't connecting the last vertex in cycle)

	for(int i = 0; i < vertices; i++)
	{
		minimum = INT_MAX;

		//alghoritm library and lambda expression used
		//	if 'i' is vertex of given path (we will check only the last vertex of path but it must be done deeper)
		if (std::any_of(path.begin(), path.end(), [i](int element) {return element == i; }))	
		{
			//must be here to prevent from out of range exception
			if (i == path[path.size() - 1])
			{
				for(int j = 0 ; j < vertices; j++)
				{
					//conditions:
					//1. not connected to itself
					//2. the smallest
					//3. not part of existing path
					if (i != j && tab[i][j] < minimum && std::none_of(path.begin(), path.end(), [j](int element) {return element == j; }))
					{
						minimum = tab[i][j];
					}
					if (i != j && tab[j][i] < minimum2 && std::none_of(path.begin(), path.end(), [j](int element) {return element == j; }))
					{
						minimum2 = tab[j][i];
					}
				}
				lb += (minimum + minimum2)/2;
			}
		}
		//if it's not found in path
		//possible vertices are: any which is not in path yet and beginning vertex
		else
		{
			for (int j = 0; j < vertices; j++)
			{
				if (i != j && tab[i][j] < minimum &&
					(std::none_of(path.begin(), path.end(), [j](int element) {return element == j; }) || j == path[0])
				   )
				{
					minimum = tab[i][j];
				}

				if (i != j && tab[j][i] < minimum2 &&
					(std::none_of(path.begin(), path.end(), [j](int element) {return element == j; }) || j == path[0])
					)
				{
					minimum2 = tab[j][i];
				}
			}
			lb += (minimum + minimum2) / 2;
		}
	}

	return lb;
}

int matrix::upperBound()
{
	int k = 1;
	int ub = 0;
	for(int i = 0; i < vertices - 1; i++)
	{
		for (int j = k; j < vertices; j++)
		{
			ub += tab[i][j];
		}
		k++;
	}
	return ub;
}

void matrix::branchAndBound(std::vector<int> cycle, int& upperBound, std::vector<int>& minCycle)
{
	//checks if cycle has vertices-1 of vertices (last one is also known then)
	if (cycle.size() == (vertices - 1))
	{
		//add last vertex and caluclate distance which is the same as lowerBound of cycle
		for (int i = 0; i < vertices; i++)
		{
			if (std::none_of(cycle.begin(), cycle.end(), [i](int elem) {return i == elem; }))
			{
				int dist = 0;
				cycle.push_back(i);
				//distance calucation
				//distance() function has better complexity than lowerBound()
				dist = distance(cycle);

				//if this is the shortest found cycle
				//upperBound is this distance/lowerBound now
				if (dist < upperBound)
				{
					//if this is the shortest found cycle
					//upperBound is this distance/lowerBound now
					upperBound = dist;
					minCycle = cycle;
				}
				return;
			}
		}
	}

	//choose next vertex to add
	//this will represent children: last vertex (new) and lowerbound for each of them
	//use this constructor to prevent realocating memory in for
	std::vector<std::pair<int, int>> possible(vertices-cycle.size(),{0,0});
	int k = 0;

	cycle.resize(cycle.size() + 1);
	for (int i = 0; i < vertices; i++)
	{
		//alghoritm library and lambda expression
		//checks if vertex 'i' is not in actual path
		if (std::none_of(cycle.begin(), cycle.end(), [i](int vertex) {return i == vertex; }))
		{
			//if it isn't then push it to possible vertices and compute lowerBound
			cycle[cycle.size() - 1] = i;
			possible[k++] = std::make_pair(i, lowerBound(cycle));
		}
	}
	cycle.resize(cycle.size() - 1);
	//now when we have all possible vertices,
	//sort them by lowerBound value which is second element in pair
	//nlog(n) complexity
	std::sort(possible.begin(), possible.end(), [](std::pair<int, int> x, std::pair<int, int> y) {return x.second < y.second; });

	//now when sorted start going deeper into tree
	//every branch should have lowerBound < upperBound
	//if it hasn't, cut the branch
	for (std::pair<int, int> element : possible)
	{
		if (element.second < upperBound)
		{
			
			cycle.push_back(element.first);
			branchAndBound(cycle, upperBound, minCycle);
			cycle.pop_back();
		}
	}
	//if every branch was checked go back higher on tree
}

void matrix::bruteForce(std::vector<int> cycle, int& minDist, std::vector<int>& minCycle)
{
	//check if it's full cycle
	if (cycle.size() == vertices)
	{
		int dist = distance(cycle);

		if (dist < minDist)
		{
			minDist = dist;
			minCycle = cycle;
			return;
		}
	}

	bool used = false;
	//choose next vertex to add
	for (int i = 0; i < vertices; i++)
	{
		used = false;

		//check if vertex is not used
		for (int j : cycle)
		{
			if (i == j)
			{
				used = true;
				break;
			}
		}
		if (!used || cycle.empty())
		{
			cycle.push_back(i);
			bruteForce(cycle, minDist, minCycle);
			cycle.pop_back();
		}
	}
}

void matrix::simulatedAnnealing(std::vector<int> cycle, std::vector<int>& cycleMin, double tempStart, double tempMin,
	double stopTime, neighbourhoodType neighbourhoodType)
{
	//Neighbourhood - group of cycles that can be created from transformation of parent cycle
	//Neighbourhood Size - number of possible unique transformations of parent cycle,
	//				size for /swap/ type is n(n-1)/2
	//Temp. Length - is value that indicates how often temperature should be decreased,
	//				should be proportional to Neighbourhood Size ( 1:2 here)
	//Temperature - starting temp. might be max or average - discribed in other functions
	//				lowering temp. is 0.95 * lastTemp, after every next step
	//Time counter - creates condition that prevent from too long calculations
	//Last Change - this is indicator of how many transformations ago was found better neighbour than actual cycle
	TimeCounter counter;
	cycleMin = cycle;
	const int tempLength = cycle.size()*(cycle.size() - 1) / 2 /2;
	double temp = tempStart;
	int lastChange = 0;
	int distanceCycleMin = distance(cycleMin);
	counter.start();

	while (counter.stop() < stopTime && lastChange < 750 && temp > tempMin)
	{
		//loop is here to keep temperature on stable level for tempLength number of transformations
		//this will create "steps" of temperature during algorithm
		for (int i = 0; i < tempLength; i++)
		{
			//choose neighbour randomly and transform with chosen type, then calculate distances
			//calculations are needed becouse of optimization
			std::vector<int> cycleNeighbour = getRandomTransformationOfVector(cycle, neighbourhoodType);
			int distanceCycle = distance(cycle);
			int distanceCycleNeighbour = distance(cycleNeighbour);

			//if neighbour is better or the same then just swap 
			//or if neighbour is worse then swap with some probability
			if (distanceCycleNeighbour - distanceCycle <= 0 ||
				distanceCycleNeighbour - distanceCycle > 0 && (double)rand() / RAND_MAX < exp(-(distanceCycleNeighbour - distanceCycle) / temp))
			{
				cycle = cycleNeighbour;
				lastChange = 0;

				//if new cycle is the shortest found then save it
				if (distanceCycleNeighbour < distanceCycleMin)
				{
					cycleMin = cycle;
					distanceCycleMin = distanceCycleNeighbour;
				}

			}

			//increment last change, if it's too big then leave 'for' loop
			lastChange++;
			if (lastChange >= 750)
			{
				break;
			}
		}

		//decrease temp when 'step' is over
		temp *= 0.95;
	}
}

double matrix::getTemperatureStartAverage(int samplesSize)
{
	//Starting temp. will be average of differences between n cycles and theirs neighbours
	double sumTemp = 0.0;
	std::vector<int> cycleParent = randomCycle();
	for (int i = 0 ; i < samplesSize; i++)
	{
		sumTemp += abs(distance(cycleParent) - distance(getRandomTransformationOfVector(cycleParent, SWAP)));
		cycleParent = randomCycle();
	}

	//caluclate average amplitude and return
	return (sumTemp / samplesSize);
}

double matrix::getTemperatureStartMax(int samplesSize)
{
	//Starting temp. will be maximum of differences between n cycles and theirs neighbours
	double maxTemp = 0.0;
	std::vector<int> cycleParent = randomCycle();
	for (int i = 0; i < samplesSize; i++)
	{
		int delta = abs(distance(cycleParent) - distance(getRandomTransformationOfVector(cycleParent, SWAP)));
		if (delta > maxTemp)
		{
			maxTemp = delta;
		}
		cycleParent = randomCycle();
	}
	return maxTemp;
}

std::vector<int> matrix::randomCycle()
{
	//to prevent from reallocating memory create vector with const size
	std::vector<int> cycle(vertices, 0);

	for (int i = 0; i < cycle.size(); i++)
	{
		//fill cycle with sorted values = i
		cycle[i] = i;
	}

	for (int i = 0; i < cycle.size(); i++)
	{
		//shuffle values randomly 
		std::swap(cycle[i], cycle[rand() % cycle.size()]);
	}
	return cycle;
}

std::vector<int> matrix::getRandomTransformationOfVector(std::vector<int> vector , neighbourhoodType type)
{
	//rand elements
	int idx1 = rand() % vector.size();
	int idx2 = rand() % vector.size();
	
	while (idx1 == idx2)
	{
		idx2 = rand() % vector.size();
	}
	//preparation
	if (idx1 > idx2)
	{
		std::swap(idx1, idx2);
	}

	//transform
	if (type == SWAP)
	{
		std::swap(vector[idx1], vector[idx2]);
	}
	else if (type == INSERT)
	{
		//insert and erase methods could be used but this would be very inefficent due to multiply realocation of memory
		int val = vector[idx2];
		for(int i = idx2 ; i > idx1; i--)
		{
			vector[i] = vector[i - 1];
		}
		vector[idx1] = val;
	}
	else if (type == INVERT)
	{
		//invert
		while (idx1 < idx2)
		{
			std::swap(vector[idx1++], vector[idx2--]);
		}
	}
	
	return vector;
}

int matrix::getVertices()
{
	return this->vertices;
}

int** matrix::getTab()
{
	return this->tab;
}

int matrix::getElement(int x, int y)
{
	if(x >= 0 && x < vertices && y >= 0 && y < vertices)
	{
		return this->tab[x][y];
	}

	return 0;
}

bool matrix::isSymetric()
{
	for (int i = 1; i < vertices; i++)
	{
		for (int j = 0; j < i; j++)
		{
				if (tab[i][j] != tab[j][i])
				{
					return false;
				}
		}
	}
	return true;
}

void matrix::changeSizeAndClear(int size)
{
	for (int i = 0; i < vertices; i++)
	{
		delete[] tab[i];
	}
	delete[] tab;

	this->vertices = size;
	tab = new int*[vertices];
	for(int i = 0; i < vertices; i++)
	{
		tab[i] = new int[vertices];
		for (int j = 0; j < vertices; ++j)
		{
			tab[i][j] = 0;
		}
	}
}

void matrix::printCycle(std::vector<int> cycle)
{
	std::cout << "CYCLE: ";
	for (int element : cycle)
	{
		std::cout << element << " <-> ";
	}
	std::cout << std::endl;
}

void matrix::addNVertex(int n)
{
	//temporary array
	int** temp = new int*[vertices + n];
	for (int i = 0; i < vertices + n; i++)
	{
		temp[i] = new int[vertices + n];
	}

	//rewrite old array
	for (int i = 0; i < vertices; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			temp[i][j] = tab[i][j];
		}
		for (int j = vertices ; j < vertices + n; j++)
		{
			temp[i][j] = 0;
		}
	}
	for (int i = vertices; i < vertices + n; i++)
	{
		for (int j = 0 ; j < vertices + n; j++)
		{
			temp[i][j] = 0;
		}
	}

	for (int i = 0; i < vertices; i++)
	{
		delete[] tab[i];
	}
	delete[] tab;

	this->vertices += n;
	tab = temp;
	
}

void matrix::addVertex()
{
	//temporary array
	int** temp = new int*[vertices + 1];
	for (int i = 0; i < vertices + 1; i++)
	{
		temp[i] = new int[vertices + 1];
	}

	//rewrite old array
	for (int i = 0; i < vertices; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			temp[i][j] = tab[i][j];
		}
		//and add empty vertex
		temp[i][vertices] = 0;
	}

	


	for (int i = 0; i < vertices; i++)
	{
		delete[] this->tab[i];
	}
	delete[] this->tab;
	this->vertices++;
	tab = temp;
}

void matrix::removeVertex()
{
	if (vertices <= 0) return;
	int n = -1;
	do
	{
		std::cout << "Podaj numer wierzcholka do usuniecia (0 - " << vertices - 1 << "):\t";
		std::cin >> n;
		std::cin.get();
	} while (n < 0);

	removeVertex(n);
}

void matrix::removeVertex(int n)
{
	if (n < 0 || n >= vertices || vertices <= 0) return;

	//temporary array
	int** temp = new int*[vertices - 1];
	for (int i = 0; i < vertices - 1; i++)
	{
		temp[i] = new int[vertices - 1];
	}

	//fill with previous values
	for (int i = 0 ; i < n; i++)
	{
		for (int j = 0 ; j < n; j++)
		{
			temp[i][j] = tab[i][j];
		}
		for (int j = n + 1; j < vertices; j++)
		{
			temp[i][j - 1] = tab[i][j];
		}
	}
	for (int i = n + 1; i < vertices; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp[i - 1][j] = tab[i][j];
		}
		for (int j = n + 1; j < vertices; j++)
		{
			temp[i - 1][j - 1] = tab[i][j];
		}
	}

	//delete old
	for (int i = 0 ; i < vertices ; i++)
	{
		delete[] tab[i];
	}
	delete[] tab;

	this->vertices--;
	this->tab = temp;
}

void matrix::fillVertexConnections(int vertex)
{
	if (vertex < 0 || vertex >= vertices) return;

	int wage = 0;

	for (int i = 0 ; i < vertices; i++)
	{
		if (vertex != i)
		{
			do
			{
				std::cout << "Insert edge of vertex for: " << i << " <-> " << vertex << ": ";
				std::cin >> wage;
			} while (wage <= 0);

			tab[i][vertex] = wage;
			tab[vertex][i] = wage;
		}
		else tab[i][i] = 0;
	}
}

void matrix::fillVertexConnectionsRandom(int vertex, int rangeDown, int rangeUp)
{
	for (int i = 0 ; i < vertices; i++)
	{
		if (i != vertex)
		{
			int num = rangeDown + rand() % (rangeUp + 1 - rangeDown);
			tab[i][vertex] = num;
			tab[vertex][i] = num;
		}
	}
}

void matrix::fillVertexConnectionsRandomUnsymmetrical(int vertex, int rangeDown, int rangeUp)
{
	for (int i = 0; i < vertices; i++)
	{
		if (i != vertex)
		{
			int num = rangeDown + rand() % (rangeUp + 1 - rangeDown);
			tab[i][vertex] = num;
			num = rangeDown + rand() % (rangeUp + 1 - rangeDown);
			tab[vertex][i] = num;
		}
	}
}

int matrix::distance(std::vector<int> vector)
{
	if (vector.empty()) return -1;
	int distance = 0;

	for (int i = 0; i < vector.size() - 1; ++i)
	{
		distance += tab[vector[i]][vector[i + 1]];
	}
	distance += tab[vector[vector.size() - 1]][vector[0]];

	return distance;
}

int matrix::distance2(std::vector<int> vector)
{
	if (vector.empty()) return -1;
	int distance = 0;

	for (int i = 0; i < vector.size() - 1; ++i)
	{
		std::cout << vector[i] << " to " << vector[i + 1] << " = " << tab[vector[i]][vector[i + 1]] << std::endl;
		distance += tab[vector[i]][vector[i + 1]];
	}
	std::cout << vector[vector.size() - 1] << " to " << vector[0] << " = " << tab[vector[vector.size() - 1]][vector[0]] << std::endl;
	distance += tab[vector[vector.size() - 1]][vector[0]];

	return distance;
}

void matrix::show()
{

	for (int i = 0; i < 32; i++)
	{
		std::cout << static_cast<char>(219);
	}

	std::cout << std::endl << "Reprezentacja macierzowa\n [" << vertices << static_cast<char>(158) << vertices << "] " << std::endl;

	for (int i = 0; i < 32; i++)
	{
		std::cout << static_cast<char>(176);
	}

	std::cout << std::endl;

	for (int i = 0; i < vertices; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			std::cout << tab[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < 32; i++)
	{
		std::cout << (char)219;
	}
	std::cout << std::endl;
}

void matrix::fillFromFile(std::string filename)
{
	this->vertices = 0;
	this->tab = nullptr;
	int i = 0, j = 0;
	int value = 0;
	int size = 0;
	std::ifstream read;
	read.open(filename);
	if (read.is_open())
	{
		read >> size;

		if (!read.fail())
		{
			this->vertices = size;

			//init tab with 0
			tab = new int*[vertices];
			for (int i = 0; i < vertices; i++)
			{
				tab[i] = new int[vertices];
				for (int j = 0; j < vertices; j++)
				{
					tab[i][j] = 0;
				}
			}

			//get values from file
			for (int k = 0; k < vertices * vertices; k++)
			{
				read >> value;
				if (!read.fail())
				{
					this->tab[i][j] = value;
					if (++j > vertices - 1)
					{
						j = 0;
						if (++i > vertices - 1)
						{
							break;
						}
					}
				}
				else
				{
					std::cout << "Read VALUE from file error." << std::endl;
					break;
				}
			}
		}
		else
		{
			std::cout << "Read SIZE from file error." << std::endl;
		}
	}
	else
	{
		std::cout << "File has NOT been opened correctly." << std::endl;
	}
}

std::vector<int> matrix::bruteForceInit()
{
	std::vector<int> min;
	if (vertices <= 0) 
	{
		std::cout << "Graph is empty!" << std::endl;
		return min;
	}

	//init path is just a first vertex of cycle pushed into vector
	//there is no sense of checking every cycle with different first vertex
	//becouse it's cycle 
	std::vector<int> initPath;
	initPath.push_back(0);

	int minDist = INT_MAX;
	bruteForce(initPath, minDist,min);

	return min;
}

std::vector<int> matrix::branchAndBoundInit()
{
	std::vector<int> min;
	if (vertices <= 0)
	{
		std::cout << "Graph is empty!" << std::endl;
		return min;
	}
	//std::cout << "WORK" << std::endl;
	//init path is just a first vertex of cycle pushed into vector
	//there is no sense of checking every cycle with different first vertex
	//becouse it's cycle 
	std::vector<int> initPath;
	initPath.push_back(0);

	int ub = upperBound();
	branchAndBound(initPath, ub, min);

	return min;
}

std::vector<int> matrix::bruteForceInit(TimeCounter& counter)
{
	counter.start();
	std::vector<int> min = bruteForceInit();
	counter.stop();

	return  min;
}

std::vector<int> matrix::branchAndBoundInit(TimeCounter& counter)
{
	counter.start();
	std::vector<int> min = branchAndBoundInit();
	counter.stop();

	return  min;
}

std::vector<int> matrix::simulatedAnnealingInit()
{
	std::vector<int> minCycle;
	simulatedAnnealing(randomCycle(), minCycle, getTemperatureStartAverage(1000), 0.01, 30, SWAP);
	return minCycle;
}

std::vector<int> matrix::simulatedAnnealingInit(neighbourhoodType type, double maxTime, TimeCounter& counter)
{
	std::vector<int> minCycle;
	counter.start();
	simulatedAnnealing(randomCycle(), minCycle, getTemperatureStartAverage(1000), 0.01, maxTime*1000, type);
	counter.stop();
	return minCycle;
}

matrix& matrix::operator=(const matrix& m)
{
	if (this == &m)
	{
		return *this;
	}

	this->vertices = m.vertices;

	this->tab = new int*[vertices];
	for (int i = 0; i < vertices; i++)
	{
		this->tab[i] = new int[vertices];
	}

	for (int i = 0; i < vertices; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			this->tab[i][j] = m.tab[i][j];
		}
	}

	return *this;
}
