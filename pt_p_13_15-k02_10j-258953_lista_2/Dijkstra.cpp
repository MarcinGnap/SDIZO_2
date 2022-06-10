#include "Dijkstra.h"

using namespace std;

Path Dijkstra::findShortestPath(IncidentMatrix* incidentMatrix, size_t from, size_t to)
{
	//	Stworzenie potrzebnych zmiennych.
	Path result;
	CellType** matrix = incidentMatrix->getMatrix();
	size_t vertexNumber = incidentMatrix->getVertexNumber();
	size_t edgesNumer = incidentMatrix->getEdgeNumber();
	size_t* values = incidentMatrix->getValues();
	//	Stworzenie tablicy przechowuj¹cej informacjê czy wierzcho³ek zosta³ ju¿ odwiedzony.
	bool* visitedVertices = new bool[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		visitedVertices[i] = false;
	}
	//	Stworzenie pocz¹tkowej wagi.
	size_t* travelCosts = new size_t[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		travelCosts[i] = SIZE_MAX;
	}

	//	Stworzenie tablicy przechowuj¹cej poprzednie wierzcho³ki.
	size_t* reachableFrom = new size_t[vertexNumber];

	for (size_t vertex = 0; vertex < vertexNumber; vertex++)
	{
		reachableFrom[vertex] = SIZE_MAX;
	}

	//	Stworzenie tablicy do przechowywania pojedyñczych wag.
	size_t* reachableFor = new size_t[vertexNumber];

	travelCosts[from] = 0;
	size_t currentVertex = from;
	size_t unvisitedVerticesNumber = vertexNumber;

	//	Znalezienie nowego wierzcho³ka.
	auto assignNewCurrentVertex = [&]()
	{
		visitedVertices[currentVertex] = true;
		unvisitedVerticesNumber--;
		size_t sortestPath = SIZE_MAX;
		for (size_t vertex = 0; vertex < vertexNumber; vertex++)
		{
			if (visitedVertices[vertex] == false && travelCosts[vertex] < sortestPath)
			{
				sortestPath = travelCosts[vertex];
				currentVertex = vertex;
			}
		}
	};

	//	Wykona siê, jesli istniej¹ jakiekolwiek nieodwiedzone wierzcho³ki.
	while (unvisitedVerticesNumber > 0)
	{
		//	Iteracja przez wszystkie krawêdzie.
		for (size_t edge = 0; edge < edgesNumer; edge++)
		{
			if (matrix[currentVertex][edge] != CellType::origin)
			{
				continue;
			}

			//	Iteracja przez wszystkie wierzcho³ki.
			for (size_t vertex = 0; vertex < vertexNumber; vertex++)
			{
				if (matrix[vertex][edge] != CellType::destination)
				{
					continue;
				}

				//	Sprawdzenie czy aktualna waga jest mniejsza ni¿ stara.
				if (travelCosts[currentVertex] + values[edge] < travelCosts[vertex])
				{
					travelCosts[vertex] = travelCosts[currentVertex] + values[edge];
					reachableFrom[vertex] = currentVertex;
					reachableFor[vertex] = values[edge];
				}

				break;
			}
		}

		//	Przypisanie nowego wierzcho³ka.
		assignNewCurrentVertex();
	}

	currentVertex = to;

	//	Stworzenie najkrótszej drogi.
	while (currentVertex != from)
	{
		//	Sprawdzenie czy po³¹czenie istnieje.
		if (currentVertex == SIZE_MAX)
		{
			return Path();
		}

		result.addEdge(PathEdge(reachableFor[currentVertex], reachableFrom[currentVertex], currentVertex));
		currentVertex = reachableFrom[currentVertex];
	}

	return result;
}

Path Dijkstra::findShortestPath(NeighborhoodList* neighborhoodList, size_t from, size_t to)
{
	//	Stworzenie potrzebnych zmiennych. 
	Path result;
	Edge** edges = neighborhoodList->getEdges();
	size_t vertexNumber = neighborhoodList->getVertexNumber();

	//	Stworzenie tablicy przechowuj¹cej informacje czy czy dany wierzcho³ek zosta³ ju¿ odwiedzony.
	bool* visitedVertices = new bool[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		visitedVertices[i] = false;
	}

	//	Stworzenie pocz¹tkowych wag.
	size_t* travelCosts = new size_t[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		travelCosts[i] = SIZE_MAX;
	}

	//	Stworzenie tablicy do przechowywania poprzednich wierzcho³ków.
	size_t* reachableFrom = new size_t[vertexNumber];

	for (size_t vertex = 0; vertex < vertexNumber; vertex++)
	{
		reachableFrom[vertex] = SIZE_MAX;
	}


	//	Stworzenie tablicy do przechowywania poszczególnych wag.
	size_t* reachableFor = new size_t[vertexNumber];

	travelCosts[from] = 0;
	size_t currentVertex = from;
	size_t unvisitedVerticesNumber = vertexNumber;

	//	Znalezienie nowego wierzcho³ka.
	auto assignNewCurrentVertex = [&]()
	{
		visitedVertices[currentVertex] = true;
		unvisitedVerticesNumber--;
		size_t sortestPath = SIZE_MAX;
		for (size_t vertex = 0; vertex < vertexNumber; vertex++)
		{
			if (visitedVertices[vertex] == false && travelCosts[vertex] < sortestPath)
			{
				sortestPath = travelCosts[vertex];
				currentVertex = vertex;
			}
		}
	};

	//	Jeœli istniej¹ nieodwiedzone wierzcho³ki.
	while (unvisitedVerticesNumber > 0)
	{
		Edge* edge = edges[currentVertex];
		while (edge != nullptr)
		{
			//	Sprawdzenie czy aktualna waga jest mniejsza od poprzedniej.
			if (travelCosts[currentVertex] + edge->value < travelCosts[edge->destination])
			{
				travelCosts[edge->destination] = travelCosts[currentVertex] + edge->value;
				reachableFrom[edge->destination] = currentVertex;
				reachableFor[edge->destination] = edge->value;
			}

			edge = edge->next;
		}

		//	Przypisanie nowego wierzcho³ka.
		assignNewCurrentVertex();
	}

	currentVertex = to;

	//	Stworzenie najkrótszej drogi.
	while (currentVertex != from)
	{
		//	Sprawdzenie czy istnieje po³¹czenie.
		if (currentVertex == SIZE_MAX)
		{
			return Path();
		}

		result.addEdge(PathEdge(reachableFor[currentVertex], reachableFrom[currentVertex], currentVertex));
		currentVertex = reachableFrom[currentVertex];
	}

	return result;
}