#include "Dijkstra.h"

using namespace std;

Path Dijkstra::findShortestPath(IncidentMatrix* incidentMatrix, size_t from, size_t to)
{
	Path result;
	CellType** matrix = incidentMatrix->getMatrix();
	size_t vertexNumber = incidentMatrix->getVertexNumber();
	size_t edgesNumer = incidentMatrix->getEdgeNumber();
	size_t* values = incidentMatrix->getValues();

	bool* visitedVertices = new bool[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		visitedVertices[i] = false;
	}

	size_t* travelCosts = new size_t[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		travelCosts[i] = SIZE_MAX;
	}

	size_t* reachableFrom = new size_t[vertexNumber];
	size_t* reachableFor = new size_t[vertexNumber];

	travelCosts[from] = 0;
	size_t currentVertex = from;
	size_t unvisitedVerticesNumber = vertexNumber;

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

	while (unvisitedVerticesNumber > 0)
	{
		for (size_t edge = 0; edge < edgesNumer; edge++)
		{
			if (matrix[currentVertex][edge] != CellType::origin)
			{
				continue;
			}

			for (size_t vertex = 0; vertex < vertexNumber; vertex++)
			{
				if (matrix[vertex][edge] != CellType::destination)
				{
					continue;
				}

				if (travelCosts[currentVertex] + values[edge] < travelCosts[vertex])
				{
					travelCosts[vertex] = travelCosts[currentVertex] + values[edge];
					reachableFrom[vertex] = currentVertex;
					reachableFor[vertex] = values[edge];
				}

				break;
			}
		}

		assignNewCurrentVertex();
	}

	currentVertex = to;

	while (currentVertex != from)
	{
		result.addEdge(PathEdge(reachableFor[currentVertex], reachableFrom[currentVertex], currentVertex));
		currentVertex = reachableFrom[currentVertex];
	}

	return result;
}

Path Dijkstra::findShortestPath(NeighborhoodList* neighborhoodList, size_t from, size_t to)
{
	Path result;
	Edge** edges = neighborhoodList->getEdges();
	size_t vertexNumber = neighborhoodList->getVertexNumber();

	bool* visitedVertices = new bool[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		visitedVertices[i] = false;
	}

	size_t* travelCosts = new size_t[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		travelCosts[i] = SIZE_MAX;
	}

	size_t* reachableFrom = new size_t[vertexNumber];
	size_t* reachableFor = new size_t[vertexNumber];

	travelCosts[from] = 0;
	size_t currentVertex = from;
	size_t unvisitedVerticesNumber = vertexNumber;

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

	while (unvisitedVerticesNumber > 0)
	{
		Edge* edge = edges[currentVertex];
		while (edge != nullptr)
		{
			if (travelCosts[currentVertex] + edge->value < travelCosts[edge->destination])
			{
				travelCosts[edge->destination] = travelCosts[currentVertex] + edge->value;
				reachableFrom[edge->destination] = currentVertex;
				reachableFor[edge->destination] = edge->value;
			}

			edge = edge->next;
		}

		assignNewCurrentVertex();
	}

	currentVertex = to;

	while (currentVertex != from)
	{
		result.addEdge(PathEdge(reachableFor[currentVertex], reachableFrom[currentVertex], currentVertex));
		currentVertex = reachableFrom[currentVertex];
	}

	return result;
}