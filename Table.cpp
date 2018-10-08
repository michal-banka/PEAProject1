#include "Table.h"
#include <thread>


Table::Table()
{
	this->size = 0;
	this->table = new int[size];
}

Table::~Table()
{
	delete[] this->table;
}

int* Table::getTable()
{
	return this->table;
}

int Table::getSize()
{
	return this->size;
}

void Table::addElementBegin(int value)
{
	int* temp = new int[size + 1];
	temp[0] = value;
	for (int i = 0 ; i < size; i++)
	{
		temp[i + 1] = table[i];
	}
	delete table;
	table = temp;
	size++;
}

void Table::addElementEnd(int value)
{
	int* temp = new int[size + 1];
	for (int i = 0; i < size; i++)
	{
		temp[i] = table[i];
	}
	temp[size] = value;
	delete table;
	table = temp;
	size++;
}

void Table::addElementAnywhere(int value, int position)
{
	int* tableTemp = new int[size + 1];
	for (int i = 0; i < position; i++)
	{
		tableTemp[i] = table[i];
	}

	tableTemp[position] = value;

	for (int i = position; i < size; i++)
	{
		tableTemp[i + 1] = table[i];
	}
	delete table;
	table = tableTemp;
	size++;
}

void Table::addElementToTable()
{
	int element = 0;
	int position = 0;

	std::cout << "Value of new element: ";
	std::cin >> element;
	std::cin.get();

	do
	{
		//adding element may happen from pos. 0 to size (as new last element)
		std::cout << "Index of new element (0 - " << size << "): ";
		std::cin >> position;
		std::cin.get();
	} while (position < 0 || position > size);

	addElementToTable(position, element);
}

/*void Table::createTable(int size)
{
	this->table = new int[size];
	this->size = 0;
}

void Table::deleteTable()
{
	delete []table;
	this->size = 0;
}

void Table::setTable(int * table, int size)
{
	this->table = table;
	this->size = size;
}*/

//position is index of place where you want to put new element
double Table::addElementToTable(int position, int newElement)
{
	if (position > size) position = size;
		if (position == 0)
		{
			counter.start();
			addElementBegin(newElement);
			return counter.stop();
		}
		else if (position == size)
		{
			counter.start();
			addElementEnd(newElement);
			return counter.stop();
		}
		else
		{
			counter.start();
			addElementAnywhere(newElement, position);
			return counter.stop();
		}
		//std::cout << "[INFO] Adding to table completed." << std::endl;
}

void Table::deleteElementBegin()
{
	if (size == 1)
	{
		delete table;
		table = new int[0];
		size = 0;
	}
	else
	{
		int* temp = new int[size - 1];
		for (int i = 0; i < size - 1; i++)
		{
			temp[i] = table[i + 1];
		}
		delete table;
		table = temp;
		size--;
	}
}

void Table::deleteElementEnd()
{
	int* temp = new int[size - 1];
	for (int i = 0; i < size - 1; i++)
	{
		temp[i] = table[i];
	}
	delete table;
	table = temp;
	size--;
}

void Table::deleteElementAnyWhere(int position)
{
	int* tableTemp = new int[size - 1];
	for (int i = 0; i < position; i++)
	{
		tableTemp[i] = table[i];
	}
	for (int i = position + 1; i < size; i++)
	{
		tableTemp[i - 1] = table[i];
	}

	delete table;
	table = tableTemp;
	size--;
}

void Table::deleteElementFromTable()
{
	if (size > 0)
	{
		int position = 0;
		do
		{
			std::cout << "Position of element to delete (0 - " << size - 1<< "): ";
			std::cin >> position;
			std::cin.get();
		} while (position < 0 || position >= size);
		deleteElementFromTable(position);
	}
	else
	{
		std::cout << "[INFO] Table is empty, nothing to delete." << std::endl << std::endl;
	}
}

//position is index of element you want to delete
double Table::deleteElementFromTable(int position)
{
	if (position == 0)
	{
		counter.start();
		deleteElementBegin();
		return counter.stop();
	}
	else if (position == size - 1)
	{
		counter.start();
		deleteElementEnd();
		return counter.stop();
	}
	else
	{
		counter.start();
		deleteElementAnyWhere(position);
		return counter.stop();
	}
}

int Table::findElementInTablePos(int value)
{
	//-1 if didn't find value
	int positionOfFoundElement = -1;

	for(int i = 0 ; i < size; i++)
	{
		if (table[i] == value)
		{
			std::cout << "[INFO] Value found in table.";
			positionOfFoundElement = i;
			break;
		}
	}

	return positionOfFoundElement;
}

void Table::fillFromFile(std::string filename)
{
	filename += ".txt";
	std::ifstream read;
	read.open(filename);
	if (read.is_open())
	{
		std::cout << "[INFO] File has been opened." << std::endl;
		size = 0;
		table = new int[size];
		int value = 0;

		while (!read.eof())
		{
			read >> value;
			addElementToTable(size,value);
		}
		std::cout << "[INFO] Filling table finished." << std::endl;
	}
	else
	{
		std::cout << "[INFO] File has NOT been opened. Table is not filled." << std::endl;
	}
	read.close();
}

void Table::saveToFile(std::string filename)
{
	filename += ".txt";
	std::ofstream write;
	write.open(filename);
	if (write.is_open())
	{
		for (int i = 0 ; i < size ; i++)
		{
			write << table[i] << std::endl;
		}
		std::cout << "[INFO] Table saved to file." << std::endl;
	}
	else
	{
		std::cout << "[INFO] File could NOT be created/opened. " << std::endl;
	}
}



void Table::showTable()
{
	if (size != 0)
	{
		std::cout << "====Table====" << std::endl;
		for (int i = 0; i < size; i++)
		{
			std::cout << "Table[" << i << "] = " << table[i] << std::endl;
		}
		std::cout << "=============" << std::endl;
		std::cout << size << ". elements in this table." << std::endl;
	}
	else
	{
		std::cout << "Table is empty." << std::endl;
	}
}

void Table::appendDoubleToTextFile(std::string filename, double dataToAppend)
{
	std::ofstream append;
	append.open(filename, std::ios::app);
	if (append.is_open())
	{
		append << dataToAppend << "\t";
	}
	else
	{
		std::cout << "[INFO] File could NOT be created or opened. Nothing has been appended." << std::endl;
	}
	append.close();
}

void Table::appendStringToTextFile(std::string filename, std::string dataToAppend)
{
	std::ofstream append;
	append.open(filename, std::ios::app);
	if (append.is_open())
	{
		append << dataToAppend;
	}
	else
	{
		std::cout << "[INFO] File could NOT be created or opened. Nothing has been appended." << std::endl;
	}
	append.close();
}

//FUNCTIONS TO RESEARCHES

double Table::addNRandomElementsToTable()
{
	int choice = 0;
	int position = 0;
	int n = 0;
	int down = 0;
	int up = 0;

	std::cout << "1. Add every new element on beggining.\n" <<
		"2. Add every new element to the end.\n" <<
		"3. Add every new element to position...\n";
	do
	{
		std::cout << "Your choice: ";
		std::cin >> choice;
		std::cin.get();
	} while (choice < 1 || choice > 3);

	if (choice == 1) position = 0;
	else if (choice == 2) position = size;
	else
	{
		std::cout << "Position of elements to add (0 - " << size << "): ";
		std::cin >> position;
		std::cin.get();
	}
	
	do
	{
		std::cout << "Number of elements to add: ";
		std::cin >> n;
		std::cin.get();
	} while (n < 0);

	std::cout << "Bottom range of elements: ";
	std::cin >> down;
	std::cin.get();

	std::cout << "Top range of elements (not less than " << n + down << "): ";
	std::cin >> up;
	std::cin.get();

	return addNRandomElementsToTable(position, n, down, up);
}

double Table::addNRandomElementsToTable(int position, int numberOfNewElements, int rangeDown, int rangeUp)
{
	double time = 0.0;
	double singleTime = 0.0;
	int val = 0;
	int* repeat = new int[rangeUp];
	for (int i = 0; i < rangeUp; i++) repeat[i] = 0;
	//with this every research will add times to different line
	appendStringToTextFile("table_add_times_data.txt", "\n");
	for (int i = 0; i < numberOfNewElements; i++)
	{
		do
		{
			val = rand() % rangeUp + rangeDown;
		} while (repeat[val] != 0);
		repeat[val] = 1;

		singleTime = addElementToTable(position, val);
		time += singleTime;
		appendDoubleToTextFile("table_add_times_data.txt",singleTime);
	}
	return time;
}

double Table::deleteAll()
{
	int choice = 0;
	int pos = 0;

	std::cout << "Choose type of deleting:\n" <<
		"1. From the end to beggining.\n" <<
		"2. From beggining to the end.\n" <<
		"3. From selected position to end, and then to beggining...\n";
	do
	{
		std::cout << "Your choice: ";
		std::cin >> choice;
		std::cin.get();
	} while (choice < 1 && choice > 3);

	if (choice == 1) pos = size - 1;
	else if (choice == 2) pos = 0;
	else
	{
		std::cout << "Insert position: ";
		std::cin >> pos;
		std::cin.get();
	}
	
	return deleteAll(pos);
}

double Table::deleteAll(int position)
{
	double singleTime = 0.0;
	double time = 0.0;
	int sizetemp = size;

	appendStringToTextFile("table_delete_times_data.txt", "\n");
	for (int i = 0 ; i < sizetemp; i++)
	{
		if (position > size - 1) position = size - 1;
		singleTime = deleteElementFromTable(position);
		time += singleTime;
		appendDoubleToTextFile("table_delete_times_data.txt", singleTime);
	}
	return time;
}

double Table::findElementInTableTime()
{
	int val = 0;
	std::cout << "Insert value to find: ";
	std::cin >> val;
	std::cin.get();
	return findElementInTableTime(val);
}

double Table::findElementInTableTime(int value)
{
	double time = 0;

	counter.start();
	for (int i = 0; i < size; i++)
	{
		if (table[i] == value)
		{
			return counter.stop()*1000;
		}
	}
	return counter.stop() * 1000;
}


