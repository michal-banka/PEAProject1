#pragma once
#include <windows.h>
#include "Libraries.h"
class TimeCounter
{
private:
	double pcFrequency;
	__int64 counterStart;
	bool pause;
public:
	TimeCounter();
	~TimeCounter();

	void start();
	double stop();
	void reset();
};

