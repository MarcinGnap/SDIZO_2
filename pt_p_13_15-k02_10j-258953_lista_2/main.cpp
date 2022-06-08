#include "mainWindow.h"

#include <iostream>
#include <random>

using namespace std;

int main()
{
	cout << "Starting..." << endl << endl;
	cout << "Press Enter to continue..." << endl;
	getchar();
	system("CLS");

	mainWindow noweOkno;
	
	noweOkno.mainMenu();

	return 0;
}