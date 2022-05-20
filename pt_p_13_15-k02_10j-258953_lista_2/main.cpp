#include "mainWindow.h"
#include <iostream>

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