#include "mainWindow.h"
#include "Reader.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "BellmanFord.h"

#include <iostream>
#include <random>

using namespace std;

int main()
{
	cout << "Starting..." << endl << endl;
	cout << "Press Enter to continue..." << endl;
	getchar();
	system("CLS");

	//mainWindow noweOkno;

	//string basePath = "D:\Foldery vD\Studia\sem 4\Projekt SDIZO 2\pt_p_13_15-k02_10j-258953_lista_2\pt_p_13_15-k02_10j-258953_lista_2/";

	Reader reader;

	auto fileName = "graph_txt.txt";

	auto from = 0;
	auto to = 0;

	auto matrix = reader.readerForMatrix(fileName);

	matrix->print(cout);

	auto list = reader.readerForList(fileName);

	list->print();

	cout << "Dijkstra" << endl;
	
	auto dijkstraMatrixPath = Dijkstra::findShortestPath(matrix, from, to);
	dijkstraMatrixPath.print(cout);

	auto dijkstraListPath = Dijkstra::findShortestPath(list, from, to);
	dijkstraListPath.print(cout);

	cout << "BellmanFord" << endl;

	auto bellmanFordMatrixPath = BellmanFord::findShortestPath(matrix, from, to);
	bellmanFordMatrixPath.print(cout);

	auto bellmanFordListPath = BellmanFord::findShortestPath(list, from, to);
	bellmanFordListPath.print(cout);

	cout << "Kruskal" << endl;

	auto kruskalMatrixMst = Kruskal::generateMst(matrix);
	kruskalMatrixMst->print(cout);
	delete kruskalMatrixMst;

	auto kruskalListMst = Kruskal::generateMst(list);
	kruskalListMst->print();
	delete kruskalListMst;

	cout << "Prim" << endl;

	auto primMatrixMst = Prim::generateMst(matrix);
	primMatrixMst->print(cout);
	delete primMatrixMst;

	auto primListMst = Prim::generateMst(list);
	primListMst->print();
	delete primListMst;

	delete matrix;
	delete list;
	
	//noweOkno.mainMenu();

	return 0;
}