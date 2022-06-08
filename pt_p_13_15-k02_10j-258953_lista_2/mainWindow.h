#pragma once
#include "timeMeasurement.h"

class mainWindow
{
public:
	mainWindow();
	~mainWindow();

	void mainMenu();
	void testsPrim(size_t, size_t);
	void testsKruskal(size_t, size_t);
	void testsDijkstra(size_t, size_t);
	void testsBellmanFord(size_t, size_t);
};