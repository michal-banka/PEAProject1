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
		
		/*if (!read.eof())
		{
			read >> number;
			this->vertices = number;
			this->tab = new int*[vertices];
			for (int i = 0; i < vertices; i++)
			{
				this->tab[i] = new int[vertices];
				
				for (int j = 0 ; j < vertices; j++)
				{
					tab[i][j] = 0;
				}
			}
		}

		
		while (!read.eof())
		{
			read >> number;
			tab[i][j] = number;
			if (++j > vertices - 1)
			{
				j = 0;
				if (++i > vertices - 1)
				{
					break;
				}
			}
		}*/
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

void matrix::hamiltionianCycleBruteForce(std::vector<int>& cycle, std::vector<int>& minCycle)
{
	std::cout << "Cycle 1: ";
	for (int e : cycle)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	//cycle and minCycle stores indexes of vertices 
	int vertex = 0;
	//if is on the last vertex
	if (cycle.size() == vertices)
	{
		std::cout << "Hamilton Tree!" << std::endl;
		int dist = 0;
		int distMin = 0;
		//first distance is unknown
		if (minCycle.empty())
		{
			int distMin = INT_MAX;
		}

		for (int i = 0; i < cycle.size() - 1; i++)
		{
			dist += tab[cycle[i]][cycle[i+1]];
			if (!minCycle.empty()) distMin += tab[minCycle[i]][minCycle[i + 1]];
		}

		//check if this cycle is shorter than minimal one
		std::cout << "Check if shorter!" << std::endl;
		std::cout << "distMin = " << distMin << ", dist = " << dist << ", tab[cycle[cycle.size() - 1]][cycle[0]] = " << tab[cycle[cycle.size() - 1]][cycle[0]] << std::endl;
		if (distMin > dist + tab[cycle[cycle.size() - 1]][cycle[0]])
		{
			minCycle = cycle;
		}
	
	}

	

	//used when hamiltonian cycle is not ready yet
	//find first not used vertex
	//so sort copy of cycle, it's little vector (size up to 30) so it won't last long with any algorithm
	std::vector<int> cycleCopy(cycle);
	std::sort(cycleCopy.begin(), cycleCopy.end(), [](int n, int m)-> bool {return n < m; });
	//now find first which is not 1 bigger than previous
	if (cycleCopy.size() >= 2 && cycleCopy.size() < vertices)
	{
		for (int i = 0; i < cycleCopy.size() - 1; i++)
		{
			if (cycleCopy[i] + 1 != cycleCopy[i+1])
			{
				vertex = cycleCopy[i] + 1;
				cycle.push_back(vertex);
			}
		}
		cycle.push_back(cycleCopy[cycleCopy.size() - 1] + 1);
		
	}
	else if (cycleCopy.size() == 1)
	{
		vertex = cycleCopy[cycleCopy.size() - 1] + 1;
		cycle.push_back(vertex);
	}
	else
	{
		vertex = 0;
		cycle.push_back(vertex);
	}
	//add vertex to cycle and recur function 
	std::cout << "Cycle 2: ";
	for (int e : cycle)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	std::cout << "Minimum Cycle: ";
	for (int e : minCycle)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	std::cin.get();
	hamiltionianCycleBruteForce(cycle, cycleCopy);
}

/*int Matrix::dijkstra(int from, int to, bool directed)
{
	struct dijkstraNode
	{
		int distance = 0;
		int previous = -1;
	};

	BidirectionalListManagement checked = BidirectionalListManagement(vertices);
	int now = from;
	int oldNow = now;
	dijkstraNode* nodes = new dijkstraNode[vertices];

	//if default value was 1000 this loop could be missed
	for (int i = 0; i < vertices; i++)
	{
		nodes[i].distance = 1000;
	}

	nodes[from].distance = 0;
	nodes[from].previous = 0;

	//now we check every vertex
	while (checked.doesValueExist(0))
	{
		oldNow = now;
		//checked.showList();
		for (int i = 0; i < edges; i++)
		{
			//first find edge connected to given fromVertex
			if (tab[i][now] < 0 && directed || tab[i][now] != 0 && !directed)
			{
				//when found, find index of toVertex
				for (int j = 0; j < vertices; j++)
				{
					//when found
					//if new path is shorter than previous change with new
					//since when abs doesn't work for ints???
					if (tab[i][j] != 0 && j != now && nodes[now].distance + abs(static_cast<double>(tab[i][now])) < nodes[j].distance)
					{
						nodes[j].distance = nodes[now].distance + abs(static_cast<double>(tab[i][now]));
						nodes[j].previous = now;
						break;
					}
				}
			}
			checked[now]->setValue(1);
		}


		//find node with the smallest node distance which has NOT been checked yet
		int min = 1000;

		for (int i = 0; i < vertices; i++)
		{
			if (nodes[i].distance < min && checked[i]->getValue() != 1)
			{
				min = nodes[i].distance;
				now = i;
			}
		}

		if (oldNow == now) break;
	}

	if (nodes[to].previous == -1)
	{
		std::cout << "Wierzcholek nie polaczony z wierzcholkiem poczatkowym." << std::endl;
		delete[] nodes;
		return -1;
	}
	else
	{
		int dist = nodes[to].distance;
		now = to;
		std::cout << "Droga: ";
		while (now != from)
		{
			std::cout << now << " <- ";
			now = nodes[now].previous;
		}
		std::cout << from << std::endl;
		delete[] nodes;
		return dist;
	}
}

int Matrix::prim(int from)
{
	struct node
	{
		int from = -1;
		int to = -1;
		int weight = 0;
	};
	//index of vertex from which we start making tree
	int now = from;
	//size of node array
	int size = 0;
	//size of tree array
	int treeSize = 0;

	int idxNode = 0;
	int cycle = false;

	node* tree = new node[treeSize];
	node* nodes = new node[size];
	node* tempNodes = new node[size + numberOfEdgesOf(now)];

	while (size > 0 || treeSize == 0)
	{
		bool inserted = false;

		//inserting new edge
		for (int i = 0; i < edges; i++)
		{
			//when edge found
			if (tab[i][now] != 0)
			{
				inserted = false;
				tempNodes = new node[size + numberOfEdgesOf(now)];

				//add new edges to nodes array
				for (int j = 0; j < size; j++)
				{
					if (nodes[j].weight > abs(tab[i][now]) && !inserted)
					{
						//find the other end of edge
						for (int k = 0; k < vertices; k++)
						{
							//and add to nodes array
							if (tab[i][k] != 0 && k != now)
							{
								tempNodes[j + 1] = { nodes[j].from, nodes[j].to, nodes[j].weight };
								tempNodes[j] = { now, k,  abs(tab[i][now]) };
								inserted = true;
							}
						}


					}
					else if (!inserted)
					{
						tempNodes[j] = { nodes[j].from, nodes[j].to, nodes[j].weight };
					}
					else
					{
						tempNodes[j + 1] = { nodes[j].from, nodes[j].to, nodes[j].weight };
					}
				}
				if (!inserted)
				{
					//find the other end of edge
					for (int k = 0; k < vertices; k++)
					{
						//and add to nodes array
						if (tab[i][k] != 0 && k != now)
						{
							tempNodes[size] = { now, k,  abs(tab[i][now]) };
							inserted = true;
						}
					}
				}
				size++;
				nodes = tempNodes;
			}
		}

		// set next node to check
		idxNode = -1;
		cycle = false;

		for (int i = 0; i < size; i++)
		{
			cycle = false;
			for (int j = 0; j < treeSize; j++)
			{
				if (tree[j].from == nodes[i].to)
				{
					cycle = true;
					break;
				}
			}

			if (!cycle)
			{
				idxNode = i;
				break;
			}
		}
		now = nodes[idxNode].to;

		//add node to tree
		node* tempTree = new node[treeSize + 1];

		for (int i = 0; i < treeSize; i++)
		{
			tempTree[i] = tree[i];
		}
		tempTree[treeSize] = nodes[idxNode];

		treeSize++;
		tree = tempTree;

		//delete nodes from 0 to idxNode
		size = size - idxNode - 1;
		node* tempN = new node[size];
		for (int i = 0; i < size; i++)
		{
			tempN[i] = nodes[i + idxNode + 1];
		}
		nodes = tempN;

		//if all vertices are on tree finish
		if (treeSize == vertices - 1) break;
	};


	//show tree
	int weight = 0;
	for (int i = 0; i < treeSize; i++)
	{
		std::cout << tree[i].from << " -> " << tree[i].to << " [" << tree[i].weight << "]" << std::endl;
		weight += tree[i].weight;
	}

	delete[] tree;
	delete[] nodes;
	delete[] tempNodes;

	return weight;
}

int Matrix::prim2(int from)
{
	BidirectionalListManagement checked = BidirectionalListManagement(vertices);
	struct primVertex
	{
		int key = 0;
		int previous = -1;
	};

	int now = from;

	primVertex* verticesPrim = new primVertex[vertices];

	for (int i = 0; i < vertices; i++)
	{
		verticesPrim[i] = { 1000, -1 };
	}

	verticesPrim[from] = { 0, from };

	//check all vertices
	while (checked.doesValueExist(0))
	{
		//check all edges of vertice now
		for (int i = 0; i < edges; i++)
		{
			if (tab[i][now] != 0)
			{
				//find the other end of this edge
				int end = 0;
				for (int j = 0; j < vertices; j++)
				{
					if (tab[i][j] != 0 && j != now)
					{
						end = j;
						break;
					}
				}

				//if key of vertice is bigger than weight of edge (now, temp->value()) set key
				if (verticesPrim[end].key > abs(tab[i][end]) && checked[end]->getValue() != 1)
				{
					verticesPrim[end] = { abs(tab[i][end]), now };
				}
				checked[now]->setValue(1);
			}
		}

		//set new now
		int min = 1000;

		for (int i = 0; i < vertices; i++)
		{
			if (verticesPrim[i].key < min && checked[i]->getValue() == 0)
			{
				min = verticesPrim[i].key;
				now = i;
			}
		}
	}

	int dist = 0;
	for (int i = 0; i < vertices; i++)
	{
		if (i != from)
		{
			dist += verticesPrim[i].key;
			std::cout << verticesPrim[i].previous << " -> " << i << " [" << verticesPrim[i].key << "]" << std::endl;
		}
	}

	delete[] verticesPrim;

	return dist;
}

int Matrix::kruskal()
{
	struct kruskalEdge
	{
		int from = -1;
		int to = -1;
		int weight = 0;
	};

	//create list of incostintent trees made out of unconected vertices
	BidirectionalListManagement checked = BidirectionalListManagement();
	//create array of all edges
	//array must be sorted
	//type of sorting will be heapsort with heap implementation from prevoius project

	//heap will be simple priority queue, we will need only first element to be correct
	//so heap is fine for that
	//and it has O(nlogn) of adding new elem, so really fast
	BinaryHeap priorityQueue = BinaryHeap();
	for (int i = 0; i < vertices; i++)
	{
		checked.addNewElementEnd(i, 0);
	}

	int from = 0, to = 0;
	bool found = false;
	for (int i = 0; i < edges; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			if (!found && tab[i][j] != 0)
			{
				from = j;
				found = true;
			}
			else if (found && tab[i][j] != 0)
			{
				to = j;
				found = false;
				break;
			}
		}
		priorityQueue.addToHeap({ from, to, tab[i][from] });
		found = false;
		to = 0, from = 0;
	}

	//array for final tree
	BinaryHeap tree = BinaryHeap();

	while (priorityQueue.getSize() != 0)
	{
		if (checked[priorityQueue.getRoot().from]->getValue() != checked[priorityQueue.getRoot().to]->getValue())
		{
			//add edge to tree
			tree.addToHeap({ priorityQueue.getRoot().from , priorityQueue.getRoot().to , priorityQueue.getRoot().weight });
			//connect subtrees
			int subtreeIdx = checked[priorityQueue.getRoot().to]->getValue();
			for (int j = 0; j < checked.getCount(); j++)
			{
				//if number of subtree is the same as second subtree
				//set this number to number of first subtree
				if (checked[j]->getValue() == subtreeIdx)
				{
					checked[j]->setValue(checked[priorityQueue.getRoot().from]->getValue());
				}
			}
		}
		priorityQueue.deleteRoot();
	}

	int distance = 0;
	std::cout << "Drzewo: " << std::endl;
	for (int i = 0; i < tree.getSize(); i++)
	{
		distance += tree[i].weight;
		std::cout << tree[i].from << "->" << tree[i].to << "[" << tree[i].weight << "]" << std::endl;
	}

	return distance;
}

int Matrix::bellman_ford(int from, int to, bool directed)
{
	struct bfEdge
	{
		int distance = 1000;
		int previous = -1;
	};

	bfEdge* verticesBF = new bfEdge[vertices];
	verticesBF[from] = { 0, from };
	bool test = true;
	int findTo = 0;
	int tempFrom = 0;
	int tempTo = 0;
	bool found = 0;

	for (int i = 0; i < vertices - 1; i++)
	{
		test = true;
		for (int j = 0; j < edges; j++)
		{
			found = false;
			tempFrom = -1;
			tempTo = -1;
			for (int k = 0; k < vertices; k++)
			{

				if (!found && tab[j][k] < 0)
				{
					tempFrom = k;
					found = true;
				}
				else if (!found && tab[j][k] > 0)
				{
					tempTo = k;
					found = true;
				}
				else if (found && tab[j][k] < 0 && k != tempTo)
				{
					tempFrom = k;
					test = false;
					break;

				}
				else if (found && tab[j][k] > 0 && k != tempFrom)
				{
					tempTo = k;
					test = false;
					break;
				}
			}

			if (verticesBF[tempFrom].distance + abs(static_cast<double>(tab[j][tempTo])) < verticesBF[tempTo].distance)
			{
				test = false;
				verticesBF[tempTo].distance = verticesBF[tempFrom].distance + abs(static_cast<double>(tab[j][tempTo]));
				verticesBF[tempTo].previous = tempFrom;
			}
		}
		if (test) break;
	}

	int now = to;
	int dist = verticesBF[now].distance;

	std::cout << "DROGA" << std::endl;
	while (now != from)
	{
		if (now == -1)
		{
			std::cout << from << " - Nie ma polaczenia tych wierzcholkow!" << std::endl;
			break;
		}
		std::cout << now << " <- ";
		now = verticesBF[now].previous;
	}
	if (now != -1) std::cout << from << std::endl;
	else
	{
		delete[] verticesBF;
		return -1;
	}

	delete[] verticesBF;

	return dist;
}
*/

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