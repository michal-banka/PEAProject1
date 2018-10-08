#pragma once
#include "Libs.h"
#include "TimeCounter.h"

class Table
{
private:
	TimeCounter counter;
	int* table;
	int size;
public:
	Table();
	~Table();

	int* getTable();
	int getSize();

	/*//use these only if it's really needed
	void createTable(int size);
	void deleteTable();
	void setTable(int* table, int size);*/
	
	void addElementBegin(int value);
	void addElementEnd(int value);
	void addElementAnywhere(int value, int position);
	void addElementToTable();
	double addElementToTable(int position, int newElement);

	void deleteElementBegin();
	void deleteElementEnd();
	void deleteElementAnyWhere(int position);
	void deleteElementFromTable();
	double deleteElementFromTable(int position);

	int findElementInTablePos(int value);

	void fillFromFile(std::string filename);
	void saveToFile(std::string filename);
	void appendDoubleToTextFile(std::string filename, double dataToAppend);
	void appendStringToTextFile(std::string filename, std::string dataToAppend);

	void showTable();
	
	//fuctions used to count time and to researches at all, they return time in ms
	double addNRandomElementsToTable();
	double addNRandomElementsToTable(int position, int numberOfNewElements, int rangeDown, int rangeUp);

	double deleteAll();
	double deleteAll(int position);

	double findElementInTableTime();
	double findElementInTableTime(int value);
};

