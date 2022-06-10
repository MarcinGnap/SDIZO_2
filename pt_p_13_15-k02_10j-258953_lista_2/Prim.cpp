#include "Prim.h"

using namespace std;

IncidentMatrix* Prim::generateMst(IncidentMatrix* incidentMatrix)
{
	//	Pozyskanie potrzebnych informacji o grafie.
	size_t vertexNumber = incidentMatrix->getVertexNumber();
	size_t edgeNumber = incidentMatrix->getEdgeNumber();
	size_t* values = incidentMatrix->getValues();
	CellType** matrix = incidentMatrix->getMatrix();
	size_t resultSize = (vertexNumber - 1) * 3;
	size_t* resultBuffor = new size_t[resultSize];
	size_t resultIndex = 0;
	EdgeHeap* heap = new EdgeHeap();

	//	Stworzenie tablicy przetrzymuj�cej informacje o odwiedzonych wierzcho�kach.
	bool* visitedVertices = new bool[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		visitedVertices[i] = false;
	}

	size_t currentVertexIndex;
	//	Dodanie do kopca kraw�dzi, kt�re mog� zosta� odwiedzone.
	auto pushReachableEdges = [&]()
	{
		//	Iteracja przez wszystkie kraw�dzie w celu znale�ienia pocz�tku.
		for (size_t begin = 0; begin < edgeNumber; begin++)
		{
			if (matrix[currentVertexIndex][begin] == CellType::empty)
			{
				continue;
			}

			//	Iteracja przez wszystkie kraw�dzie w celu znale�ienia ko�ca.
			for (size_t end = 0; end < vertexNumber; end++)
			{
				if (matrix[end][begin] == CellType::empty || end == currentVertexIndex)
				{
					continue;
				}

				if (visitedVertices[end])
				{
					continue;
				}

				//	Dodanie kraw�dzi to kopca.
				heap->push(new Edge(currentVertexIndex, end, values[begin]));
			}

		}
	};

	//	Ustawienie stanu na pocz�tkowy.
	currentVertexIndex = 0;
	visitedVertices[currentVertexIndex] = true;
	pushReachableEdges();

	//	Iteracja przez wszystkie wierczho�ki.
	for (size_t i = 0; i < vertexNumber - 1;)
	{
		Edge* candidate = heap->pop();

		//	Sprawdzenie czy docelowy wierzcho�ek z korzenia kopca zosta� ju� "odwiedzony".
		if (!visitedVertices[candidate->destination])
		{
			//	Zapisanie wyniku.
			currentVertexIndex = candidate->destination;
			resultBuffor[3 * resultIndex] = candidate->origin;
			resultBuffor[3 * resultIndex + 1] = candidate->destination;
			resultBuffor[3 * resultIndex + 2] = candidate->value;
			visitedVertices[currentVertexIndex] = true;
			pushReachableEdges();
			resultIndex++;
			i++;
		}

		delete candidate;
	}

	//	Stworzenie macierzy wynikowej.
	IncidentMatrix* result = new IncidentMatrix(vertexNumber - 1, vertexNumber, resultBuffor);
	delete[] resultBuffor;
	delete heap;

	return result;
}

NeighborhoodList* Prim::generateMst(NeighborhoodList* neighborhoodList)
{
	//	Pozyskanie potrzebnych zmiennych.
	size_t vertexNumber = neighborhoodList->getVertexNumber();
	size_t resultSize = (vertexNumber - 1) * 3;
	size_t* resultBuffor = new size_t[resultSize];
	size_t resultIndex = 0;
	Edge** edges = neighborhoodList->getEdges();
	EdgeHeap* heap = new EdgeHeap(false);
	//	Stworzenie tablicy przechowuj�cej informacje, czy wierzcho�ek zosta� odwiedzony.
	bool* visitedVertices = new bool[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		visitedVertices[i] = false;
	}

	size_t currentVertexIndex;
	//	Dodanie do kopca wszystkich kraw�dzi, kt�re mog� zosta� odwiedzone.
	auto pushReachableEdges = [&]()
	{
		//	Iteracja przez wszystkie kraw�dzie w celu znalezienia pocz�tku.
		for (size_t i = 0; i < vertexNumber; i++)
		{
			Edge* edge = edges[i];

			if (edge == nullptr)
			{
				continue;
			}

			while (edge != nullptr)
			{
				//	Sprawdzenie czy wierzcho�ek pocz�tkowy kraw�dzi zosta� ju� odwiedzony.
				if (edge->origin == currentVertexIndex && !visitedVertices[edge->destination])
				{
					heap->push(edge);
				}
				//	Sprawdzenie czy wierzcho�ek ko�cowy kraw�dzi zosta� ju� odwiedzony.
				if (edge->destination == currentVertexIndex && !visitedVertices[edge->origin])
				{
					heap->push(edge);
				}

				edge = edge->next;
			}
		}
	};
	//	Ustawienie stanu na pocz�tkowy.
	currentVertexIndex = 0;
	visitedVertices[currentVertexIndex] = true;
	pushReachableEdges();
	//	Iteracja przez wszystkie wierzcho�ki.
	for (size_t i = 0; i < vertexNumber - 1;)
	{
		Edge* candidate = heap->pop();

		if (!visitedVertices[candidate->destination] || !visitedVertices[candidate->origin])
		{
			//	Wybranie nowego wierzcho�ka.
			currentVertexIndex = visitedVertices[candidate->destination]
				? candidate->origin
				: candidate->destination;
			//	Zapisanie wyniku.
			resultBuffor[3 * resultIndex] = candidate->origin;
			resultBuffor[3 * resultIndex + 1] = candidate->destination;
			resultBuffor[3 * resultIndex + 2] = candidate->value;
			visitedVertices[currentVertexIndex] = true;
			pushReachableEdges();
			resultIndex++;
			i++;
		}
	}
	//	Stworzenie listy wynikowej.
	NeighborhoodList* result = new NeighborhoodList(vertexNumber - 1, vertexNumber, resultBuffor);
	delete[] resultBuffor;
	delete heap;

	return result;
}