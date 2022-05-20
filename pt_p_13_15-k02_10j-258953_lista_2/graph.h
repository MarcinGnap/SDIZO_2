#pragma once
#include "timeMeasurement.h"
#include "SH.h"

class Graph
{
public:


	Graph();
	~Graph();

	bool readFromFile();
	bool generate();
	bool clearAll();
	void display();

private:

};