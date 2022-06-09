#include "mainWindow.h"
#include "IncidentMatrix.h"
#include "NeighborhoodList.h"
#include "SH.h"
#include "timeMeasurement.h"
#include "Generator.h"
#include "Reader.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "BellmanFord.h"

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
	IncidentMatrix* newMatrix = nullptr;
	NeighborhoodList* newList = nullptr;
	Generator* newGenerator;
	Reader newReader;
	SH shw;
	timeMeasurement tM;

	auto fileName = "graph_txt.txt";

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

			cout << "Operacja przeprowadzana dla macierzy:\n";
			auto o1 = chrono::high_resolution_clock::now();
			newMatrix = newReader.readerForMatrix(fileName);
			auto o2 = chrono::high_resolution_clock::now();
			tM.tMOutcome(o1, o2);

			newMatrix->print();

			cout << "Operacja przeprowadzana dla listy:\n";
			auto o3 = chrono::high_resolution_clock::now();
			newList = newReader.readerForList(fileName);
			auto o4 = chrono::high_resolution_clock::now();
			tM.tMOutcome(o3, o4);

			newList->print();

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

			auto o1 = chrono::high_resolution_clock::now();
			RawGraphData newData = newGenerator->generate(fDensity, stVertexNum, stMaxValue);
			auto o2 = chrono::high_resolution_clock::now();

			newMatrix = new IncidentMatrix(newData.edgeNumber, newData.vertexNumber, newData.data);
			newList = new NeighborhoodList(newData.edgeNumber, newData.vertexNumber, newData.data);
			auto o3 = chrono::high_resolution_clock::now();

			cout << "Wygenerowanie danych zajelo:\n" << tM.tMShort(o1, o2) << endl;
			cout << "Zbudowanie z dostepnych danych macierzy i listy zajelo:\n" << tM.tMShort(o2, o3) << endl;

			shw.done();
			break;
		}
		case 3:
		{
			cout << "Usuniecie danych.\n";

			auto o1 = chrono::high_resolution_clock::now();
			delete newMatrix;
			auto o2 = chrono::high_resolution_clock::now();
			tM.tMOutcome(o1, o2);
			
			auto o3 = chrono::high_resolution_clock::now();
			delete newList;
			auto o4 = chrono::high_resolution_clock::now();
			tM.tMOutcome(o3, o4);

			shw.done();
			break;
		}
		case 4:
		{
			cout << "Wyswietlenie grafu.\n" 
					"Macierz incydencji:\n";

			auto o1 = chrono::high_resolution_clock::now();
			newMatrix->print();
			auto o2 = chrono::high_resolution_clock::now();
			tM.tMOutcome(o1, o2);

			cout << "\n \n Lista sasiedztwa: \n";

			auto o3 = chrono::high_resolution_clock::now();
			newList->print();
			auto o4 = chrono::high_resolution_clock::now();
			tM.tMOutcome(o3, o4);
			shw.done();
			break;
		}
		case 5:
		{
			cout << "Algorytm Prima.\n";

			auto o1 = chrono::high_resolution_clock::now();
			auto primMatrixMst = Prim::generateMst(newMatrix);
			auto o2 = chrono::high_resolution_clock::now();

			primMatrixMst->print();
			tM.tMOutcome(o1, o2);

			delete primMatrixMst;

			auto o3 = chrono::high_resolution_clock::now();
			auto primListMst = Prim::generateMst(newList);
			auto o4 = chrono::high_resolution_clock::now();

			primListMst->print();
			tM.tMOutcome(o3, o4);

			delete primListMst;

			shw.done();
			break;
		}
		case 6:
		{
			cout << "Algorytm Kruskala.\n";

			auto o1 = chrono::high_resolution_clock::now();
			auto kruskalMatrixMst = Kruskal::generateMst(newMatrix);
			auto o2 = chrono::high_resolution_clock::now();

			kruskalMatrixMst->print();
			tM.tMOutcome(o1, o2);

			delete kruskalMatrixMst;

			auto o3 = chrono::high_resolution_clock::now();
			auto KruskalListMst = Kruskal::generateMst(newList);
			auto o4 = chrono::high_resolution_clock::now();

			KruskalListMst->print();
			tM.tMOutcome(o3, o4);

			delete KruskalListMst;

			shw.done();
			break;
		}
		case 7:
		{
			size_t from, to;
			cout << "Algorytm Dijkstry.\n"
					"Wybierz wierzcholek startowy:\n";
			cin >> from;
			cout << "Wybierz wierzcholek koncowy:\n";
			cin >> to;
			cout << "Algorytm przeprowadzany dla macierzy incydencji:\n";

			auto o1 = chrono::high_resolution_clock::now();
			auto dijkstraMatrixPath = Dijkstra::findShortestPath(newMatrix, from, to);
			auto o2 = chrono::high_resolution_clock::now();

			dijkstraMatrixPath.print(cout);
			tM.tMOutcome(o1, o2);

			cout << "Algorytm przeprowadzany dla listy sasiedztwa:\n";
			auto o3 = chrono::high_resolution_clock::now();
			auto dijkstraListPath = Dijkstra::findShortestPath(newList, from, to);
			auto o4 = chrono::high_resolution_clock::now();

			dijkstraListPath.print(cout);
			tM.tMOutcome(o3, o4);

			shw.done();
			break;
		}
		case 8:
		{
			size_t from, to;
			cout << "Algorytm Forda-Bellmana.\n";
				"Wybierz wierzcholek startowy:\n";
			cin >> from;
			cout << "Wybierz wierzcholek koncowy:\n";
			cin >> to;

			auto o1 = chrono::high_resolution_clock::now();
			auto bellmanFordMatrixPath = BellmanFord::findShortestPath(newMatrix, from, to);
			auto o2 = chrono::high_resolution_clock::now();

			bellmanFordMatrixPath.print(cout);
			tM.tMOutcome(o1, o2);

			auto o3 = chrono::high_resolution_clock::now();
			auto bellmanFordListPath = BellmanFord::findShortestPath(newList, from, to);
			auto o4 = chrono::high_resolution_clock::now();

			bellmanFordListPath.print(cout);
			tM.tMOutcome(o3, o4);

			shw.done();
			break;
		}
		case 9:
		{
			cout << "Pomiary czasu.\n";
			size_t trialsNumber;
			size_t firstVertexNumber = 20;
			size_t secondVertexNumber = 50;
			size_t thirdVertexNumber = 80;
			size_t fourthVertexNumber = 110;
			size_t fifthVertexNumber = 140;

			cout << "Podaj liczbe pomiarow jaka ma zostac przeprowadzona:\n";
			cin >> trialsNumber;

			cout << "Prim:\n";
			cout << "For " << firstVertexNumber << "...\n";
			testsPrim(trialsNumber, firstVertexNumber);
			cout << "First done\n";
			cout << "For " << secondVertexNumber << "...\n";
			testsPrim(trialsNumber, secondVertexNumber);
			cout << "Second done\n";
			cout << "For " << thirdVertexNumber << "...\n";
			testsPrim(trialsNumber, thirdVertexNumber);
			cout << "Third done\n";
			cout << "For " << fourthVertexNumber << "...\n";
			testsPrim(trialsNumber, fourthVertexNumber);
			cout << "Fourth done\n";
			cout << "For " << fifthVertexNumber << "...\n";
			testsPrim(trialsNumber, fifthVertexNumber);
			cout << "Fifth done\n";

			cout << "Kruskal:\n";
			cout << "For " << firstVertexNumber << "...\n";
			testsKruskal(trialsNumber, firstVertexNumber);
			cout << "First done\n";
			cout << "For " << secondVertexNumber << "...\n";
			testsKruskal(trialsNumber, secondVertexNumber);
			cout << "Second done\n";
			cout << "For " << thirdVertexNumber << "...\n";
			testsKruskal(trialsNumber, thirdVertexNumber);
			cout << "Third done\n";
			cout << "For " << fourthVertexNumber << "...\n";
			testsKruskal(trialsNumber, fourthVertexNumber);
			cout << "Fourth done\n";
			cout << "For " << fifthVertexNumber << "...\n";
			testsKruskal(trialsNumber, fifthVertexNumber);
			cout << "Fifth done\n";

			cout << "Dijkstra:\n";
			cout << "For " << firstVertexNumber << "...\n";
			testsDijkstra(trialsNumber, firstVertexNumber);
			cout << "First done\n";
			cout << "For " << secondVertexNumber << "...\n";
			testsDijkstra(trialsNumber, secondVertexNumber);
			cout << "Second done\n";
			cout << "For " << thirdVertexNumber << "...\n";
			testsDijkstra(trialsNumber, thirdVertexNumber);
			cout << "Third done\n";
			cout << "For " << fourthVertexNumber << "...\n";
			testsDijkstra(trialsNumber, fourthVertexNumber);
			cout << "Fourth done\n";
			cout << "For " << fifthVertexNumber << "...\n";
			testsDijkstra(trialsNumber, fifthVertexNumber);
			cout << "Fifth done\n";

			cout << "Bellman Ford:\n";
			cout << "For " << firstVertexNumber << "...\n";
			testsBellmanFord(trialsNumber, firstVertexNumber);
			cout << "First done\n";
			cout << "For " << secondVertexNumber << "...\n";
			testsBellmanFord(trialsNumber, secondVertexNumber);
			cout << "Second done\n";
			cout << "For " << thirdVertexNumber << "...\n";
			testsBellmanFord(trialsNumber, thirdVertexNumber);
			cout << "Third done\n";
			cout << "For " << fourthVertexNumber << "...\n";
			testsBellmanFord(trialsNumber, fourthVertexNumber);
			cout << "Fourth done\n";
			cout << "For " << fifthVertexNumber << "...\n";
			testsBellmanFord(trialsNumber, fifthVertexNumber);
			cout << "Fifth done\n";

			cout <<	"All done...\n";

			shw.done();
			break;
		}
		case 0:
		{
			//	Wyjœcie z programu.
			exit(0);
			break;
		}
		default:
		{
			shw.noOption();
		}
		}
	}
}

void mainWindow::testsPrim(size_t trialsNumber, size_t vertexNumber)
{
	Generator* tempGenerator;
	timeMeasurement tMTests;

	int fMatrixAvg = 0;
	int fListAvg = 0;
	int sMatrixAvg = 0;
	int sListAvg = 0;
	int tMatrixAvg = 0;
	int tListAvg = 0;
	int cMatrixAvg = 0;
	int cListAvg = 0;

	float firstDensity = 0.25;
	float secondDensity = 0.5;
	float thirdDensity = 0.75;
	float fourthDensity = 0.99;

	srand(time(0));

	//	Pierwsza gêstoœæ.
	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(firstDensity, vertexNumber, maxVal);
		IncidentMatrix* tempMatrix;
		tempMatrix = new IncidentMatrix(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempMatrixMst = Prim::generateMst(tempMatrix);
		auto o2 = chrono::high_resolution_clock::now();

		fMatrixAvg = fMatrixAvg + tMTests.tMTest(o1, o2);

		delete tempMatrix;
	}

	fMatrixAvg = fMatrixAvg / trialsNumber;

	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(firstDensity, vertexNumber, maxVal);
		NeighborhoodList* tempList;
		tempList = new NeighborhoodList(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempListMst = Prim::generateMst(tempList);
		auto o2 = chrono::high_resolution_clock::now();

		fListAvg = fListAvg + tMTests.tMTest(o1, o2);

		delete tempList;
	}

	fListAvg = fListAvg / trialsNumber;

	//	Druga gêstoœæ.
	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(secondDensity, vertexNumber, maxVal);
		IncidentMatrix* tempMatrix;
		tempMatrix = new IncidentMatrix(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempMatrixMst = Prim::generateMst(tempMatrix);
		auto o2 = chrono::high_resolution_clock::now();

		sMatrixAvg = sMatrixAvg + tMTests.tMTest(o1, o2);

		delete tempMatrix;
	}

	sMatrixAvg = sMatrixAvg / trialsNumber;

	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(secondDensity, vertexNumber, maxVal);
		NeighborhoodList* tempList;
		tempList = new NeighborhoodList(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempListMst = Prim::generateMst(tempList);
		auto o2 = chrono::high_resolution_clock::now();

		sListAvg = sListAvg + tMTests.tMTest(o1, o2);

		delete tempList;
	}

	sListAvg = sListAvg / trialsNumber;

	//	Trzecia gêstoœæ.
	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(thirdDensity, vertexNumber, maxVal);
		IncidentMatrix* tempMatrix;
		tempMatrix = new IncidentMatrix(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempMatrixMst = Prim::generateMst(tempMatrix);
		auto o2 = chrono::high_resolution_clock::now();

		tMatrixAvg = tMatrixAvg + tMTests.tMTest(o1, o2);

		delete tempMatrix;
	}
	
	tMatrixAvg = tMatrixAvg / trialsNumber;

	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(thirdDensity, vertexNumber, maxVal);
		NeighborhoodList* tempList;
		tempList = new NeighborhoodList(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempListMst = Prim::generateMst(tempList);
		auto o2 = chrono::high_resolution_clock::now();

		tListAvg = tListAvg + tMTests.tMTest(o1, o2);

		delete tempList;
	}

	tListAvg = tListAvg / trialsNumber;

	//	Czwarta gêstoœæ.
	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(fourthDensity, vertexNumber, maxVal);
		IncidentMatrix* tempMatrix;
		tempMatrix = new IncidentMatrix(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempMatrixMst = Prim::generateMst(tempMatrix);
		auto o2 = chrono::high_resolution_clock::now();

		cMatrixAvg = cMatrixAvg + tMTests.tMTest(o1, o2);

		delete tempMatrix;
	}

	cMatrixAvg = cMatrixAvg / trialsNumber;

	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(fourthDensity, vertexNumber, maxVal);
		NeighborhoodList* tempList;
		tempList = new NeighborhoodList(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempListMst = Prim::generateMst(tempList);
		auto o2 = chrono::high_resolution_clock::now();

		cListAvg = cListAvg + tMTests.tMTest(o1, o2);

		delete tempList;
	}

	cListAvg = cListAvg / trialsNumber;

	cout << "Czas przeprowadzania algorytmu Prima dla macierzy:\n"
		"\t - dla gestosci " << firstDensity << " wynosi:\n \t" << fMatrixAvg << endl;
	cout << "\t - dla gestosci " << secondDensity << " wynosi: \t" << sMatrixAvg << endl;
	cout << "\t - dla gestosci " << thirdDensity << " wynosi: \t" << tMatrixAvg << endl;
	cout << "\t - dla gestosci " << fourthDensity << " wynosi: \t" << cMatrixAvg << endl;

	cout << "Czas przeprowadzania algorytmu Prima dla listy:\n"
		"\t - dla gestosci " << firstDensity << " wynosi:\n \t" << fListAvg << endl;
	cout << "\t - dla gestosci " << secondDensity << " wynosi: \t" << sListAvg << endl;
	cout << "\t - dla gestosci " << thirdDensity << " wynosi: \t" << tListAvg << endl;
	cout << "\t - dla gestosci " << fourthDensity << " wynosi: \t" << cListAvg << endl;
}

void mainWindow::testsKruskal(size_t trialsNumber, size_t vertexNumber)
{
	Generator* tempGenerator;
	timeMeasurement tMTests;

	int fMatrixAvg = 0;
	int fListAvg = 0;
	int sMatrixAvg = 0;
	int sListAvg = 0;
	int tMatrixAvg = 0;
	int tListAvg = 0;
	int cMatrixAvg = 0;
	int cListAvg = 0;

	float firstDensity = 0.25;
	float secondDensity = 0.5;
	float thirdDensity = 0.75;
	float fourthDensity = 0.99;

	srand(time(0));

	//	Pierwsza gêstoœæ.
	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(firstDensity, vertexNumber, maxVal);
		IncidentMatrix* tempMatrix;
		tempMatrix = new IncidentMatrix(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempMatrixMst = Kruskal::generateMst(tempMatrix);
		auto o2 = chrono::high_resolution_clock::now();

		fMatrixAvg = fMatrixAvg + tMTests.tMTest(o1, o2);

		delete tempMatrix;
	}

	fMatrixAvg = fMatrixAvg / trialsNumber;

	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(firstDensity, vertexNumber, maxVal);
		NeighborhoodList* tempList;
		tempList = new NeighborhoodList(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempListMst = Kruskal::generateMst(tempList);
		auto o2 = chrono::high_resolution_clock::now();

		fListAvg = fListAvg + tMTests.tMTest(o1, o2);

		delete tempList;
	}

	fListAvg = fListAvg / trialsNumber;

	//	Druga gêstoœæ.
	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(secondDensity, vertexNumber, maxVal);
		IncidentMatrix* tempMatrix;
		tempMatrix = new IncidentMatrix(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempMatrixMst = Kruskal::generateMst(tempMatrix);
		auto o2 = chrono::high_resolution_clock::now();

		sMatrixAvg = sMatrixAvg + tMTests.tMTest(o1, o2);

		delete tempMatrix;
	}

	sMatrixAvg = sMatrixAvg / trialsNumber;

	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(secondDensity, vertexNumber, maxVal);
		NeighborhoodList* tempList;
		tempList = new NeighborhoodList(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempListMst = Kruskal::generateMst(tempList);
		auto o2 = chrono::high_resolution_clock::now();

		sListAvg = sListAvg + tMTests.tMTest(o1, o2);

		delete tempList;
	}

	sListAvg = sListAvg / trialsNumber;

	//	Trzecia gêstoœæ.
	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(thirdDensity, vertexNumber, maxVal);
		IncidentMatrix* tempMatrix;
		tempMatrix = new IncidentMatrix(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempMatrixMst = Kruskal::generateMst(tempMatrix);
		auto o2 = chrono::high_resolution_clock::now();

		tMatrixAvg = tMatrixAvg + tMTests.tMTest(o1, o2);

		delete tempMatrix;
	}

	tMatrixAvg = tMatrixAvg / trialsNumber;

	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(thirdDensity, vertexNumber, maxVal);
		NeighborhoodList* tempList;
		tempList = new NeighborhoodList(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempListMst = Kruskal::generateMst(tempList);
		auto o2 = chrono::high_resolution_clock::now();

		tListAvg = tListAvg + tMTests.tMTest(o1, o2);

		delete tempList;
	}

	tListAvg = tListAvg / trialsNumber;

	//	Czwarta gêstoœæ.
	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(fourthDensity, vertexNumber, maxVal);
		IncidentMatrix* tempMatrix;
		tempMatrix = new IncidentMatrix(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempMatrixMst = Kruskal::generateMst(tempMatrix);
		auto o2 = chrono::high_resolution_clock::now();

		cMatrixAvg = cMatrixAvg + tMTests.tMTest(o1, o2);

		delete tempMatrix;
	}

	cMatrixAvg = cMatrixAvg / trialsNumber;

	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(fourthDensity, vertexNumber, maxVal);
		NeighborhoodList* tempList;
		tempList = new NeighborhoodList(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempListMst = Kruskal::generateMst(tempList);
		auto o2 = chrono::high_resolution_clock::now();

		cListAvg = cListAvg + tMTests.tMTest(o1, o2);

		delete tempList;
	}

	cListAvg = cListAvg / trialsNumber;

	cout << "Czas przeprowadzania algorytmu Kruskala dla macierzy:\n"
		"\t - dla gestosci " << firstDensity << " wynosi: \t" << fMatrixAvg << endl;
	cout << "\t - dla gestosci " << secondDensity << " wynosi: \t" << sMatrixAvg << endl;
	cout << "\t - dla gestosci " << thirdDensity << " wynosi: \t" << tMatrixAvg << endl;
	cout << "\t - dla gestosci " << fourthDensity << " wynosi: \t" << cMatrixAvg << endl;

	cout << "Czas przeprowadzania algorytmu Kruskala dla listy:\n"
		"\t - dla gestosci " << firstDensity << " wynosi: \t" << fListAvg << endl;
	cout << "\t - dla gestosci " << secondDensity << " wynosi: \t" << sListAvg << endl;
	cout << "\t - dla gestosci " << thirdDensity << " wynosi: \t" << tListAvg << endl;
	cout << "\t - dla gestosci " << fourthDensity << " wynosi: \t" << cListAvg << endl;
}

void mainWindow::testsDijkstra(size_t trialsNumber, size_t vertexNumber)
{
	Generator* tempGenerator;
	timeMeasurement tMTests;

	int fMatrixAvg = 0;
	int fListAvg = 0;
	int sMatrixAvg = 0;
	int sListAvg = 0;
	int tMatrixAvg = 0;
	int tListAvg = 0;
	int cMatrixAvg = 0;
	int cListAvg = 0;

	float firstDensity = 0.25;
	float secondDensity = 0.5;
	float thirdDensity = 0.75;
	float fourthDensity = 0.99;

	srand(time(0));

	//	Pierwsza gêstoœæ.
	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(firstDensity, vertexNumber, maxVal);
		IncidentMatrix* tempMatrix;
		tempMatrix = new IncidentMatrix(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempMatrixPath = ;
		auto o2 = chrono::high_resolution_clock::now();

		fMatrixAvg = fMatrixAvg + tMTests.tMTest(o1, o2);

		delete tempMatrix;
	}

	fMatrixAvg = fMatrixAvg / trialsNumber;

	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(firstDensity, vertexNumber, maxVal);
		NeighborhoodList* tempList;
		tempList = new NeighborhoodList(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempListPath = ;
		auto o2 = chrono::high_resolution_clock::now();

		fListAvg = fListAvg + tMTests.tMTest(o1, o2);

		delete tempList;
	}

	fListAvg = fListAvg / trialsNumber;

	//	Druga gêstoœæ.
	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(secondDensity, vertexNumber, maxVal);
		IncidentMatrix* tempMatrix;
		tempMatrix = new IncidentMatrix(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempMatrixPath = ;
		auto o2 = chrono::high_resolution_clock::now();

		sMatrixAvg = sMatrixAvg + tMTests.tMTest(o1, o2);

		delete tempMatrix;
	}

	sMatrixAvg = sMatrixAvg / trialsNumber;

	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(secondDensity, vertexNumber, maxVal);
		NeighborhoodList* tempList;
		tempList = new NeighborhoodList(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempListPath = ;
		auto o2 = chrono::high_resolution_clock::now();

		sListAvg = sListAvg + tMTests.tMTest(o1, o2);

		delete tempList;
	}

	sListAvg = sListAvg / trialsNumber;

	//	Trzecia gêstoœæ.
	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(thirdDensity, vertexNumber, maxVal);
		IncidentMatrix* tempMatrix;
		tempMatrix = new IncidentMatrix(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempMatrixPath = ;
		auto o2 = chrono::high_resolution_clock::now();

		tMatrixAvg = tMatrixAvg + tMTests.tMTest(o1, o2);

		delete tempMatrix;
	}

	tMatrixAvg = tMatrixAvg / trialsNumber;

	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(thirdDensity, vertexNumber, maxVal);
		NeighborhoodList* tempList;
		tempList = new NeighborhoodList(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempListPath = ;
		auto o2 = chrono::high_resolution_clock::now();

		tListAvg = tListAvg + tMTests.tMTest(o1, o2);

		delete tempList;
	}

	tListAvg = tListAvg / trialsNumber;

	//	Czwarta gêstoœæ.
	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(fourthDensity, vertexNumber, maxVal);
		IncidentMatrix* tempMatrix;
		tempMatrix = new IncidentMatrix(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempMatrixPath = ;
		auto o2 = chrono::high_resolution_clock::now();

		cMatrixAvg = cMatrixAvg + tMTests.tMTest(o1, o2);

		delete tempMatrix;
	}

	cMatrixAvg = cMatrixAvg / trialsNumber;

	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(fourthDensity, vertexNumber, maxVal);
		NeighborhoodList* tempList;
		tempList = new NeighborhoodList(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempListPath = ;
		auto o2 = chrono::high_resolution_clock::now();

		cListAvg = cListAvg + tMTests.tMTest(o1, o2);

		delete tempList;
	}

	cListAvg = cListAvg / trialsNumber;

	cout << "Czas przeprowadzania algorytmu Dijkstry dla macierzy:\n"
		"\t - dla gestosci " << firstDensity << " wynosi:\n \t" << fMatrixAvg << endl;
	cout << "\t - dla gestosci " << secondDensity << " wynosi:\n \t" << sMatrixAvg << endl;
	cout << "\t - dla gestosci " << thirdDensity << " wynosi:\n \t" << tMatrixAvg << endl;
	cout << "\t - dla gestosci " << fourthDensity << " wynosi:\n \t" << cMatrixAvg << endl;

	cout << "Czas przeprowadzania algorytmu Prima dla listy:\n"
		"\t - dla gestosci " << firstDensity << " wynosi:\n \t" << fListAvg << endl;
	cout << "\t - dla gestosci " << secondDensity << " wynosi:\n \t" << sListAvg << endl;
	cout << "\t - dla gestosci " << thirdDensity << " wynosi:\n \t" << tListAvg << endl;
	cout << "\t - dla gestosci " << fourthDensity << " wynosi:\n \t" << cListAvg << endl;
}

void mainWindow::testsBellmanFord(size_t trialsNumber, size_t vertexNumber)
{
	Generator* tempGenerator;
	timeMeasurement tMTests;

	int fMatrixAvg = 0;
	int fListAvg = 0;
	int sMatrixAvg = 0;
	int sListAvg = 0;
	int tMatrixAvg = 0;
	int tListAvg = 0;
	int cMatrixAvg = 0;
	int cListAvg = 0;

	float firstDensity = 0.25;
	float secondDensity = 0.5;
	float thirdDensity = 0.75;
	float fourthDensity = 0.99;

	srand(time(0));

	//	Pierwsza gêstoœæ.
	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(firstDensity, vertexNumber, maxVal);
		IncidentMatrix* tempMatrix;
		tempMatrix = new IncidentMatrix(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempMatrixPath = ;
		auto o2 = chrono::high_resolution_clock::now();

		fMatrixAvg = fMatrixAvg + tMTests.tMTest(o1, o2);

		delete tempMatrix;
	}

	fMatrixAvg = fMatrixAvg / trialsNumber;

	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(firstDensity, vertexNumber, maxVal);
		NeighborhoodList* tempList;
		tempList = new NeighborhoodList(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempListPath = ;
		auto o2 = chrono::high_resolution_clock::now();

		fListAvg = fListAvg + tMTests.tMTest(o1, o2);

		delete tempList;
	}

	fListAvg = fListAvg / trialsNumber;

	//	Druga gêstoœæ.
	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(secondDensity, vertexNumber, maxVal);
		IncidentMatrix* tempMatrix;
		tempMatrix = new IncidentMatrix(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempMatrixPath = ;
		auto o2 = chrono::high_resolution_clock::now();

		sMatrixAvg = sMatrixAvg + tMTests.tMTest(o1, o2);

		delete tempMatrix;
	}

	sMatrixAvg = sMatrixAvg / trialsNumber;

	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(secondDensity, vertexNumber, maxVal);
		NeighborhoodList* tempList;
		tempList = new NeighborhoodList(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempListPath = ;
		auto o2 = chrono::high_resolution_clock::now();

		sListAvg = sListAvg + tMTests.tMTest(o1, o2);

		delete tempList;
	}

	sListAvg = sListAvg / trialsNumber;

	//	Trzecia gêstoœæ.
	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(thirdDensity, vertexNumber, maxVal);
		IncidentMatrix* tempMatrix;
		tempMatrix = new IncidentMatrix(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempMatrixPath = ;
		auto o2 = chrono::high_resolution_clock::now();

		tMatrixAvg = tMatrixAvg + tMTests.tMTest(o1, o2);

		delete tempMatrix;
	}

	tMatrixAvg = tMatrixAvg / trialsNumber;

	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(thirdDensity, vertexNumber, maxVal);
		NeighborhoodList* tempList;
		tempList = new NeighborhoodList(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempListPath = ;
		auto o2 = chrono::high_resolution_clock::now();

		tListAvg = tListAvg + tMTests.tMTest(o1, o2);

		delete tempList;
	}

	tListAvg = tListAvg / trialsNumber;

	//	Czwarta gêstoœæ.
	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(fourthDensity, vertexNumber, maxVal);
		IncidentMatrix* tempMatrix;
		tempMatrix = new IncidentMatrix(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempMatrixPath = ;
		auto o2 = chrono::high_resolution_clock::now();

		cMatrixAvg = cMatrixAvg + tMTests.tMTest(o1, o2);

		delete tempMatrix;
	}

	cMatrixAvg = cMatrixAvg / trialsNumber;

	for (int i = 0; i < trialsNumber; i++)
	{
		size_t maxVal = rand();
		RawGraphData tempData = tempGenerator->generate(fourthDensity, vertexNumber, maxVal);
		NeighborhoodList* tempList;
		tempList = new NeighborhoodList(tempData.edgeNumber, tempData.vertexNumber, tempData.data);

		auto o1 = chrono::high_resolution_clock::now();
		auto tempListPath = ;
		auto o2 = chrono::high_resolution_clock::now();

		cListAvg = cListAvg + tMTests.tMTest(o1, o2);

		delete tempList;
	}

	cListAvg = cListAvg / trialsNumber;

	cout << "Czas przeprowadzania algorytmu Prima dla macierzy:\n"
		"\t - dla gestosci " << firstDensity << " wynosi:\n \t" << fMatrixAvg << endl;
	cout << "\t - dla gestosci " << secondDensity << " wynosi:\n \t" << sMatrixAvg << endl;
	cout << "\t - dla gestosci " << thirdDensity << " wynosi:\n \t" << tMatrixAvg << endl;
	cout << "\t - dla gestosci " << fourthDensity << " wynosi:\n \t" << cMatrixAvg << endl;

	cout << "Czas przeprowadzania algorytmu Prima dla listy:\n"
		"\t - dla gestosci " << firstDensity << " wynosi:\n \t" << fListAvg << endl;
	cout << "\t - dla gestosci " << secondDensity << " wynosi:\n \t" << sListAvg << endl;
	cout << "\t - dla gestosci " << thirdDensity << " wynosi:\n \t" << tListAvg << endl;
	cout << "\t - dla gestosci " << fourthDensity << " wynosi:\n \t" << cListAvg << endl;
}