#include "mainWindow.h"
#include "IncidentMatrix.h"
#include "NeighborhoodList.h"
#include "SH.h"
#include "Generator.h"
#include "Reader.h"

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
	size_t tab[] = {
		0, 1, 2,
		0, 2, 4,
		1, 2, 2,
		1, 3, 4,
		1, 4, 2,
		2, 4, 3,
		3, 4, 3,
		3, 5, 2,
		4, 5, 2
	};

	auto newMatrix = new IncidentMatrix(9, 6, tab);
	auto newList = new NeighborhoodList(9, 6, tab);
	auto newGenerator = new Generator();
	SH shw;

	short sMChoice;

	for (;;)					//	Pêtla, w której dzia³a g³ówne menu.
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
			"\t9.Test.\n"
			"\t0.Wyjscie.\n";
		cin >> sMChoice;

		switch (sMChoice)
		{
		case 1:
		{
			cout << "Wczytanie danych z pliku tekstowego.\n";
			shw.done();
			break;
		}
		case 2:
		{
			cout << "Wygenerowanie danych losowo.\n";
			float fDensity;
			size_t stVertexNum, stMaxValue;
			cout << "Wybierz gestosc grafu: ";
			cin >> fDensity;
			cout << "Wybierz ilosc wierzcholkow: ";
			cin >> stVertexNum;
			cout << "Wybierz maksymalna wage krawedzi: ";
			cin >> stMaxValue;
			newMatrix = nullptr;
			newList = nullptr;
			RawGraphData newData = newGenerator->generate(fDensity, stVertexNum, stMaxValue);
			newMatrix = new IncidentMatrix(newData.edgeNumber, newData.vertexNumber, newData.data);
			newList = new NeighborhoodList(newData.edgeNumber, newData.vertexNumber, newData.data);
			shw.done();
			break;
		}
		case 3:
		{
			cout << "Usuniecie danych.\n";
			shw.done();
			break;
		}
		case 4:
		{
			cout << "Wyswietlenie grafu.\n" 
					"Macierz incydencji:\n";
			newMatrix->print(cout);
			cout << "\n \n Lista sasiedztwa: \n";
			newList->print();
			shw.done();
			break;
		}
		case 5:
		{
			cout << "Algorytm Prima.\n";
			shw.done();
			break;
		}
		case 6:
		{
			cout << "Algorytm Kruskala.\n";
			shw.done();
			break;
		}
		case 7:
		{
			cout << "Algorytm Dijkstry.\n";
			shw.done();
			break;
		}
		case 8:
		{
			cout << "Algorytm Forda-Bellmana.\n";
			shw.done();
			break;
		}
		case 9:
		{
			cout << "Pomiary czasu.\n"
				"Aka Test\n";



			shw.done();
			break;
		}
		case 0:
		{
			exit(0);					//	Wyjœcie z programu.
			break;
		}
		default:
		{
			shw.noOption();
		}
		}
	}
}