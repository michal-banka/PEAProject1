#include "TimeCounter.h"



TimeCounter::TimeCounter()
{
	this->counterStart = 0;
	this->pcFrequency = 0.0;
}


TimeCounter::~TimeCounter()
{
}

double TimeCounter::getTime()
{
	return this->time;
}

void TimeCounter::start()
{
	LARGE_INTEGER largeInt;
	if (!QueryPerformanceFrequency(&largeInt))
	{
		std::cout << "[INFO] Start timer problem." << std::endl;
	}

	// divide 1000 to get miliseconds
	pcFrequency = (double)largeInt.QuadPart ;

	QueryPerformanceCounter(&largeInt);
	counterStart = largeInt.QuadPart;
}

double TimeCounter::stop()
{
	LARGE_INTEGER largeInt;
	QueryPerformanceCounter(&largeInt);
	time = double(largeInt.QuadPart - counterStart) / pcFrequency;
	return double(largeInt.QuadPart - counterStart) / pcFrequency;
}

void TimeCounter::reset()
{
	this->counterStart = 0;
	this->pcFrequency = 0.0;
}
