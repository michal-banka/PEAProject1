#include "Table.h"



table::table()
{
	this->size = 0;
	this->tab = new int[0];
}


table::table(int size)
{
	this->size = size;
	this->tab = new int[size];
}

table::table(int* tab, int size)
{
	this->size = size;
	this->tab = tab;
}

table::~table()
{
	delete[]this->tab;
}

int table::getValue(int idx)
{
	if (idx < 0 || idx >= this->size)
	{
		return -1;
	}
	else
	{
		return tab[idx];
	}
}

int table::getSize()
{
	return this->size;
}

int* table::getTab()
{
	return this->tab;
}

void table::push_back(int value)
{
	int* temp = new int(this->size + 1);
	for (int i = 0 ; i < this->size; i++)
	{
		temp[i] = this->tab[i];
	}
	temp[this->size] = value;
	this->size++;
	delete[] tab;
	this->tab = temp;
}

void table::push_front(int value)
{
	int* temp = new int(this->size + 1);
	temp[0] = value;
	for (int i = 0; i < this->size; i++)
	{
		temp[i + 1] = this->tab[i];
	}
	
	this->size++;
	delete[]this->tab;
	this->tab = temp;
}

void table::push_in(int value, int idx)
{
	if (idx < 0 || idx > size) return;

	int* temp = new int(this->size + 1);
	for (int i = 0; i < idx; i++)
	{
		temp[i] = this->tab[i];
	}
	temp[idx] = value;
	for (int i = idx; i < this->size; i++)
	{
		temp[i + 1] = this->tab[i];
	}

	this->size++;
	delete[]tab;
	tab = temp;
}

void table::pop_back()
{
	int* temp = new int(this->size - 1);
	for (int i = 0; i < this->size - 1; i++)
	{
		temp[i] = this->tab[i];
	}

	this->size--;
	delete[]tab;
	tab = temp;
}

void table::pop_front()
{
	int* temp = new int(this->size - 1);
	for (int i = 0; i < this->size - 1; i++)
	{
		temp[i] = this->tab[i + 1];
	}

	this->size--;
	delete[]tab;
	tab = temp;
}

void table::pop_in(int idx)
{
	int* temp = new int(this->size - 1);
	for (int i = 0; i < this->size - 1; ++i)
	{
		if (i < idx)
		{
			temp[i] = tab[i];
		}
		else
		{
			temp[i] = tab[i + 1];
		}
	}

	this->size--;
	delete[]tab;
	tab = temp;
}

void table::show()
{
	std::cout << "TABLE: ";
	for (int i = 0; i < size; ++i)
	{
		std::cout << tab[i] << " ";
	}
	std::cout << std::endl;
}



