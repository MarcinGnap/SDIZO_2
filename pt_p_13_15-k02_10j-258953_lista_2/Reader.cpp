#include "Reader.h"

using namespace std;

//	Odczytywanie dla macierzy.
IncidentMatrix* Reader::readerForMatrix(string fileName) {
	size_t edgeNumber;
	size_t vertexNumber;
	size_t* data;

	//	Otworzenie pliku do odczytania.
	std::ifstream file(fileName);

	//	Odczytanie z pierwszej linii ilo�ci kraw�dzi oraz ilo�ci wierzcho�k�w.
	file >> edgeNumber >> vertexNumber;

	//	Utworzenie tablicy o rozmiarze 3 krotnie wi�kszym ni� ilo�� kraw�dzi, poniewa� w ka�dej linijce pliku tekstowego s� 3 warto�ci.
	data = new size_t[edgeNumber * 3];

	//	Odczytywanie ca�ej zawarto�ci pliku i wpisywanie do tablicy.
	for (size_t i = 0; i < edgeNumber * 3; i++)
		file >> data[i];

	//	Utworzenie obiektu struktury z zebranych danych.
	IncidentMatrix* matrix = new IncidentMatrix(edgeNumber, vertexNumber, data);

	delete[] data;

	return matrix;
}

//	Odczytywanie dla listy jest tanalogiczne do odczytywania dla macierzy.
NeighborhoodList* Reader::readerForList(string fileName) {
	size_t edgeNumber;
	size_t vertexNumber;
	size_t* data;

	std::ifstream file(fileName);

	file >> edgeNumber >> vertexNumber;

	data = new size_t[edgeNumber * 3];

	for (size_t i = 0; i < edgeNumber * 3; i++)
		file >> data[i];

	NeighborhoodList* list = new NeighborhoodList(edgeNumber, vertexNumber, data);

	delete[] data;

	return list;
}