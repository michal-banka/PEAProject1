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



/*void Matrix::setTab(int** tab)
{
	this->tab = tab;
}

void Matrix::setEdges(int edges)
{
	this->edges = edges;
}

void Matrix::setVertices(int vertices)
{
	this->vertices = vertices;
}*/


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
		//and add empty vertice
		temp[i][vertices] = 0;
	}

	this->vertices++;


	for (int i = 0; i < vertices; i++)
	{
		delete[] tab[i];
	}
	delete[] tab;

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
				std::cout << "Podaj wage krawedzi " << i << " <-> " << vertex << ": ";
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

std::vector<int> matrix::hamiltionianCycleBruteForceInit()
{
	std::vector<int> empty;
	std::vector<int> min;
	int minDist = INT_MAX;
	min = hamiltionianCycleBruteForce(empty, minDist,min);

	std::cout << "Minimal cycle with brute force method: ";
	for (int element : min)
	{
		std::cout << element << " <-> ";
	}
	std::cout << min[0];
	std::cout << std::endl;
	std::cout << "Minimal distance: " << minDist;


	return empty;
}

std::vector<int> matrix::branchAndBound(Tree* subtree)
{
	//add vertices as children which are not used yet
	for(int i = 0 ; i < vertices; i++)
	{
		bool found = false;
		for (int j = 0; j < subtree->getSubsolution().size(); ++j)
		{
			if (subtree->getSubsolution()[j] == vertices)
			{
				found = true;
			}
		}

		if (!found)
		{
			//subtree->addChild(new Tree(subtree->getChildren()[i], nullptr, );
		}
	}
	return std::vector<int>(4);
}

std::vector<int> matrix::hamiltionianCycleBruteForce(std::vector<int> cycle, int& minDist, std::vector<int> minCycle)
{	
	//check if it's full cycle
	if (cycle.size() == vertices)
	{
		int distance = 0;
		for (int i = 0 ; i < cycle.size() - 1; i++)
		{
			distance += tab[cycle[i]][cycle[i + 1]];
		}
		distance += tab[cycle[cycle.size() - 1]][cycle[0]];

		if (distance < minDist)
		{
			minDist = distance;
			minCycle = cycle;
			return cycle;
		}
		else
		{
			return minCycle;
		}
	}

	bool used = false;
	//choose next vertex to add
	for(int i = 0 ; i < vertices; i++)
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
			minCycle = hamiltionianCycleBruteForce(cycle, minDist,minCycle);
			cycle.pop_back();
		}
	}
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