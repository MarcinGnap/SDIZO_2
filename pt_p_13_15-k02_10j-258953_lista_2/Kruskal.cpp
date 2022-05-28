#include "Kruskal.h"

using namespace std;

IncidentMatrix* Kruskal::generateMst(IncidentMatrix* incidentMatrix)
{
	size_t vertexNumber = incidentMatrix->getVertexNumber();
	size_t edgeNumber = incidentMatrix->getEdgeNumber();
	size_t* values = incidentMatrix->getValues();
	CellType** matrix = incidentMatrix->getMatrix();
	size_t resultSize = (vertexNumber - 1) * 3;
	size_t* resultBuffor = new size_t[resultSize];
	size_t resultIndex = 0;
	EdgeHeap* heap = new EdgeHeap();

	size_t* treeIds = new size_t[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		treeIds[i] = i;
	}

	Edge* tempEdge = nullptr;
	for (size_t edge = 0; edge < edgeNumber; edge++)
	{
		tempEdge = new Edge(-1, -1, values[edge]);

		for (size_t vertex = 0; vertex < vertexNumber; vertex++)
		{
			if (matrix[vertex][edge] == CellType::origin)
			{
				tempEdge->origin = vertex;
			}

			if (matrix[vertex][edge] == CellType::destination)
			{
				tempEdge->destination = vertex;
			}

			heap->push(tempEdge);
		}
	}

	while (!heap->empty())
	{
		tempEdge = heap->pop();

		if (treeIds[tempEdge->origin] != treeIds[tempEdge->destination])
		{
			resultBuffor[3 * resultIndex] = tempEdge->origin;
			resultBuffor[3 * resultIndex + 1] = tempEdge->destination;
			resultBuffor[3 * resultIndex + 2] = tempEdge->value;

			int oldTreeId = treeIds[tempEdge->origin];
			int newTreeId = treeIds[tempEdge->destination];
			for (size_t id = 0; id < vertexNumber; id++)
			{
				if (treeIds[id] == oldTreeId)
				{
					treeIds[id] = newTreeId;
				}
			}

			resultIndex++;
		}
	}

	IncidentMatrix* result = new IncidentMatrix(vertexNumber - 1, vertexNumber, resultBuffor);
	delete[] resultBuffor;
	delete heap;
	return result;
}

NeighborhoodList* Kruskal::generateMst(NeighborhoodList* neighborhoodList)
{
	size_t vertexNumber = neighborhoodList->getVertexNumber();
	size_t resultSize = (vertexNumber - 1) * 3;
	size_t* resultBuffor = new size_t[resultSize];
	size_t resultIndex = 0;
	Edge** edges = neighborhoodList->getEdges();
	EdgeHeap* heap = new EdgeHeap(false);

	size_t* treeIds = new size_t[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		treeIds[i] = i;
	}

	Edge* tempEdge = nullptr;
	for (size_t vertex = 0; vertex < vertexNumber; vertex++)
	{
		tempEdge = edges[vertex];

		while (tempEdge != nullptr)
		{
			heap->push(tempEdge);
			tempEdge = tempEdge->next;
		}
	}

	while (!heap->empty())
	{
		tempEdge = heap->pop();

		if (treeIds[tempEdge->origin] != treeIds[tempEdge->destination])
		{
			resultBuffor[3 * resultIndex] = tempEdge->origin;
			resultBuffor[3 * resultIndex + 1] = tempEdge->destination;
			resultBuffor[3 * resultIndex + 2] = tempEdge->value;

			int oldTreeId = treeIds[tempEdge->origin];
			int newTreeId = treeIds[tempEdge->destination];
			for (size_t id = 0; id < vertexNumber; id++)
			{
				if (treeIds[id] == oldTreeId)
					treeIds[id] = newTreeId;
			}

			resultIndex++;
		}
	}

	NeighborhoodList* result = new NeighborhoodList(vertexNumber - 1, vertexNumber, resultBuffor);
	delete[] resultBuffor;
	delete heap;
	return result;
}