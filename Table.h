#pragma once
#include "Libs.h"
class table
{
private:
	int* tab;
	int size;
public:
	table();
	table(int size);
	table(int* tab, int size);
	~table();

	int getValue(int idx);
	int getSize();
	int* getTab();

	void push_back(int value);
	void push_front(int value);
	void push_in(int value, int idx);
	void pop_back();
	void pop_front();
	void pop_in(int idx);

	void show();
};

