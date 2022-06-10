#include "timeMeasurement.h"

#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;

/*
	Klasa obs³uguj¹ca pomiar czasu.
*/

//	Metody wyœwietlaj¹ca czas operacji dziêki przekazanym parametrom.

//	Wyœwietlenie pe³nego zdania.
void timeMeasurement::tMOutcome(chrono::high_resolution_clock::time_point o1, chrono::high_resolution_clock::time_point o2)
{
	chrono::nanoseconds time_span = chrono::duration_cast<chrono::nanoseconds> (o2 - o1);
	cout << "\nWykonanie operacji zajelo " << time_span.count() << " nanosekund." << endl;
}

//	Wyœwietlenie niepe³nego zdania.
long long timeMeasurement::tMShort(chrono::high_resolution_clock::time_point o1, chrono::high_resolution_clock::time_point o2)
{
	chrono::nanoseconds time_span = chrono::duration_cast<chrono::nanoseconds> (o2 - o1);
	cout << "* " << time_span.count() << " nanosekund" << endl;
	
	return time_span.count();
}

//	Wyœwietlenie tylko wyniku.
long long timeMeasurement::tMTest(chrono::high_resolution_clock::time_point o1, chrono::high_resolution_clock::time_point o2)
{
	chrono::nanoseconds time_span = chrono::duration_cast<chrono::nanoseconds> (o2 - o1);

	return time_span.count();
}