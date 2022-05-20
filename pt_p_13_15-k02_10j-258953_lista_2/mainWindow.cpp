#include "mainWindow.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

mainWindow::mainWindow()
{

}

mainWindow::~mainWindow()
{

}

void mainWindow::mainMenu()
{
	short sMChoice;

	for (;;)					//	P�tla, w kt�rej dzia�a g��wne menu.
	{
		system("CLS");

		cout << "Prosze wybrac: \n"
			"\t1.Wczytanie danych z pliku tekstowego. \n"
			"\t2.Wygenerowanie danych losowo.\n"
			"\t3.Usuniecie danych.\n"
			"\t4.Wyswietlenie grafu.\n"
			"\t5.Algorytm Prima.\n"
			"\t6.Algorytm Kruskala.\n"
			"\t7.Algorytm Dijkstry.\n"
			"\t8.Algorytm Forda-Bellmana.\n"
			"\t9.Algorytm Forda-Fulkersona.\n"
			"\t0.Wyjscie.\n";
		cin >> sMChoice;

		switch (sMChoice)
		{
		case 1:
		{
			cout << "Wczytanie danych z pliku tekstowego.\n";
			break;
		}
		case 2:
		{
			cout << "Wygenerowanie danych losowo.\n";
			break;
		}
		case 3:
		{
			cout << "Usuniecie danych.\n";
			break;
		}
		case 4:
		{
			cout << "Wyswietlenie grafu.\n";
			break;
		}
		case 5:
		{
			cout << "Algorytm Prima.\n";
			break;
		}
		case 6:
		{
			cout << "Algorytm Kruskala.\n";
			break;
		}
		case 7:
		{
			cout << "Algorytm Dijkstry.\n";
			break;
		}
		case 8:
		{
			cout << "Algorytm Forda-Bellmana.\n";
			break;
		}
		case 9:
		{
			cout << "Algorytm Forda-Fulkersona.\n";
			break;
		}
		case 0:
		{
			exit(0);					//	Wyj�cie z programu.
			break;
		}
		default:
		{
			cout << "Nie ma takiej opcji...\n"
				"Prosze wybrac cos innego...\n";
			getchar();		//	Po wybraniu innej opcji ni� jest to przewidziane wy�wietla si� komunikat 
			getchar();		//	oraz program "czeka" na naci�ni�cie klawisza "enter".
			break;			//	Wyst�puje tu podw�jny getchar() ze wzgl�du na to, i� pojedy�czy nie wykonuje swojego zadania.
		}
		}
	}
}