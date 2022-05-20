#pragma once
#include "timeMeasurement.h"
#include "SH.h"
#include "array.h"

class Graph
{
public:
	unsigned int uiGTopAmount;
	Array aTop;

	Graph();
	~Graph();

	bool readFromFile();
	bool generate();
	bool clearAll();
	void display();

private:

};