#pragma once
#include <windows.h>
#include "Libs.h"
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

