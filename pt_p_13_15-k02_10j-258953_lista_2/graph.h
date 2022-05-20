#pragma once
#include "timeMeasurement.h"
#include "SH.h"

class graph
{
public:


	graph();
	~graph();

	bool readFromFile();
	bool generate();
	bool clearAll();
	void display();

private:

};