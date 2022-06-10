#include "timeMeasurement.h"

#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;

/*
	Klasa obs�uguj�ca pomiar czasu.
*/

//	Metody wy�wietlaj�ca czas operacji dzi�ki przekazanym parametrom.

//	Wy�wietlenie pe�nego zdania.
void timeMeasurement::tMOutcome(chrono::high_resolution_clock::time_point o1, chrono::high_resolution_clock::time_point o2)
{
	chrono::nanoseconds time_span = chrono::duration_cast<chrono::nanoseconds> (o2 - o1);
	cout << "\nWykonanie operacji zajelo " << time_span.count() << " nanosekund." << endl;
}

//	Wy�wietlenie niepe�nego zdania.
long long timeMeasurement::tMShort(chrono::high_resolution_clock::time_point o1, chrono::high_resolution_clock::time_point o2)
{
	chrono::nanoseconds time_span = chrono::duration_cast<chrono::nanoseconds> (o2 - o1);
	cout << "* " << time_span.count() << " nanosekund" << endl;
	
	return time_span.count();
}

//	Wy�wietlenie tylko wyniku.
long long timeMeasurement::tMTest(chrono::high_resolution_clock::time_point o1, chrono::high_resolution_clock::time_point o2)
{
	chrono::nanoseconds time_span = chrono::duration_cast<chrono::nanoseconds> (o2 - o1);

	return time_span.count();
}