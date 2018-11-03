#pragma once
#include <windows.h>
#include "Libs.h"
class TimeCounter
{
private:
	double pcFrequency;
	__int64 counterStart;
	double time;
public:
	TimeCounter();
	~TimeCounter();

	double getTime();

	void start();
	double stop();
	void reset();
};

