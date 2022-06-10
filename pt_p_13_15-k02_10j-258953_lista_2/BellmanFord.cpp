#include "BellmanFord.h"

Path BellmanFord::findShortestPath(IncidentMatrix* incidentMatrix, size_t from, size_t to)
{
	//	Pozyskanie potrzebnych danych.
	Path result;
	CellType** matrix = incidentMatrix->getMatrix();
	size_t vertexNumber = incidentMatrix->getVertexNumber();
	size_t edgesNumer = incidentMatrix->getEdgeNumber();
	size_t* values = incidentMatrix->getValues();

	//	Wygenerowanie pocz�tkowych wag.
	size_t* travelCosts = new size_t[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		travelCosts[i] = SIZE_MAX;
	}

	//	Stworzenie tablicy do przechowywania poprzednich wierzcho�k�w.
	size_t* reachableFrom = new size_t[vertexNumber];

	for (size_t vertex = 0; vertex < vertexNumber; vertex++)
	{
		reachableFrom[vertex] = SIZE_MAX;
	}

	//	Stworzenie tablicy przechowuj�cej poszczeg�lne wagi.
	size_t* reachableFor = new size_t[vertexNumber];

	travelCosts[from] = 0;

	bool anyChange = true;
	//	P�tla wykonuj�ca si� o jeden raz mniej ni� ilo�� wierzcho�k�w.
	for (size_t i = 0; (i < vertexNumber - 1) && anyChange; i++)
	{
		anyChange = false;
		//	Iteracja przez wszystkie wierzcho�ki.
		for (size_t origin = 0; origin < vertexNumber; origin++)
		{
			//	Sprawdzenie czy wierzcho�ek by� ju� odwiedzony.
			if (travelCosts[origin] == SIZE_MAX)
			{
				continue;
			}

			//	Iteracja przez wszystkie kraw�dzie.
			for (size_t edge = 0; edge < edgesNumer; edge++)
			{
				if (matrix[origin][edge] != CellType::origin)
				{
					continue;
				}

				//	Znalezienie docelowego wierzcho�ka.
				for (size_t destination = 0; destination < edgesNumer; destination++)
				{
					if (matrix[destination][edge] != CellType::destination)
					{
						continue;
					}

					//	Sprawdzenie czy aktualna waga jest ni�sza od poprzedniej.
					if (travelCosts[origin] + values[edge] < travelCosts[destination])
					{
						anyChange = true;
						travelCosts[destination] = travelCosts[origin] + values[edge];
						reachableFrom[destination] = origin;
						reachableFor[destination] = values[edge];
					}

					break;
				}
			}
		}
	}

	size_t currentVertex = to;

	//	Stworzenie najkr�tszej drogi.
	while (currentVertex != from)
	{
		//	Sprawdzenie czy istnieje po��czenie.
		if (currentVertex == SIZE_MAX)
		{
			return Path();
		}

		result.addEdge(PathEdge(reachableFor[currentVertex], reachableFrom[currentVertex], currentVertex));
		currentVertex = reachableFrom[currentVertex];
	}

	return result;
}

Path BellmanFord::findShortestPath(NeighborhoodList* neighborhoodList, size_t from, size_t to)
{
	//	Pozyskanie potrzebnych danych.
	Path result;
	Edge** edges = neighborhoodList->getEdges();
	size_t vertexNumber = neighborhoodList->getVertexNumber();

	//	Wygenerowanie pocz�tkowych wag.
	size_t* travelCosts = new size_t[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		travelCosts[i] = SIZE_MAX;
	}

	//	Stworzenie tablicy przechowuj�cej poprzednie wierzcho�ki.
	size_t* reachableFrom = new size_t[vertexNumber];

	for (size_t vertex = 0; vertex < vertexNumber; vertex++)
	{
		reachableFrom[vertex] = SIZE_MAX;
	}

	//	Stworzenie tablicy przechowuj�cej poszczeg�lne wagi.
	size_t* reachableFor = new size_t[vertexNumber];

	travelCosts[from] = 0;

	Edge* edge = nullptr;
	bool anyChange = true;
	//	P�tla wykonuj�ca si� o jeden raz mniej ni� ilo�� wierzcho�k�w.
	for (size_t i = 0; i < (vertexNumber - 1) && anyChange; i++)
	{
		anyChange = false;

		//	Iteracja przez wszystkie wierzcho�ki.
		for (size_t j = 0; j < vertexNumber; j++)
		{
			//	Sprawdzenie czy dany wierzcho�ek by� ju� odwiedzony.
			if (travelCosts[j] == SIZE_MAX)
			{
				continue;
			}

			Edge* edge = edges[j];
			while (edge != nullptr)
			{
				//	Sprawdzenie czy aktualna waga jest ni�sza od poprzedniej.
				if (travelCosts[j] + edge->value < travelCosts[edge->destination])
				{
					anyChange = true;
					travelCosts[edge->destination] = travelCosts[j] + edge->value;
					reachableFrom[edge->destination] = j;
					reachableFor[edge->destination] = edge->value;
				}

				edge = edge->next;
			}
		}
	}

	size_t currentVertex = to;

	//	Stworzenie najkr�tszej drogi.
	while (currentVertex != from)
	{
		//	Sprawdzenie czy po��czenie istnieje.
		if (currentVertex == SIZE_MAX)
		{
			return Path();
		}

		result.addEdge(PathEdge(reachableFor[currentVertex], reachableFrom[currentVertex], currentVertex));
		currentVertex = reachableFrom[currentVertex];
	}

	return result;
}