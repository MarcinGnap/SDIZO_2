#include "Prim.h"

using namespace std;

IncidentMatrix* Prim::generateMst(IncidentMatrix* incidentMatrix)
{
	size_t vertexNumber = incidentMatrix->getVertexNumber();
	size_t edgeNumber = incidentMatrix->getEdgeNumber();
	size_t* values = incidentMatrix->getValues();
	CellType** matrix = incidentMatrix->getMatrix();
	size_t resultSize = (vertexNumber - 1) * 3;
	size_t* resultBuffor = new size_t[resultSize];
	size_t resultIndex = 0;
	EdgeHeap* heap = new EdgeHeap();

	bool* visitedVertices = new bool[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		visitedVertices[i] = false;
	}

	size_t currentVertexIndex;
	auto pushReachableEdges = [&]()
	{
		for (size_t begin = 0; begin < edgeNumber; begin++)
		{
			if (matrix[currentVertexIndex][begin] == CellType::empty)
			{
				continue;
			}

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

				heap->push(new Edge(currentVertexIndex, end, values[begin]));
			}

		}
	};

	currentVertexIndex = 0;
	visitedVertices[currentVertexIndex] = true;
	pushReachableEdges();

	for (size_t i = 0; i < vertexNumber - 1;)
	{
		Edge* candidate = heap->pop();

		if (!visitedVertices[candidate->destination])
		{
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

	IncidentMatrix* result = new IncidentMatrix(vertexNumber - 1, vertexNumber, resultBuffor);
	delete[] resultBuffor;
	delete heap;
	return result;
}

NeighborhoodList* Prim::generateMst(NeighborhoodList* neighborhoodList)
{
	size_t vertexNumber = neighborhoodList->getVertexNumber();
	size_t resultSize = (vertexNumber - 1) * 3;
	size_t* resultBuffor = new size_t[resultSize];
	size_t resultIndex = 0;
	Edge** edges = neighborhoodList->getEdges();
	EdgeHeap* heap = new EdgeHeap(false);

	bool* visitedVertices = new bool[vertexNumber];
	for (size_t i = 0; i < vertexNumber; i++)
	{
		visitedVertices[i] = false;
	}

	size_t currentVertexIndex;
	auto pushReachableEdges = [&]()
	{
		for (size_t i = 0; i < vertexNumber; i++)
		{
			Edge* edge = edges[i];

			if (edge == nullptr)
			{
				continue;
			}

			while (edge != nullptr)
			{
				if (edge->origin == currentVertexIndex && !visitedVertices[edge->destination])
				{
					heap->push(edge);
				}

				if (edge->destination == currentVertexIndex && !visitedVertices[edge->origin])
				{
					heap->push(edge);
				}

				edge = edge->next;
			}
		}
	};

	currentVertexIndex = 0;
	visitedVertices[currentVertexIndex] = true;
	pushReachableEdges();

	for (size_t i = 0; i < vertexNumber - 1;)
	{
		Edge* candidate = heap->pop();

		if (!visitedVertices[candidate->destination] || !visitedVertices[candidate->origin])
		{
			currentVertexIndex = visitedVertices[candidate->destination]
				? candidate->origin
				: candidate->destination;
			resultBuffor[3 * resultIndex] = candidate->origin;
			resultBuffor[3 * resultIndex + 1] = candidate->destination;
			resultBuffor[3 * resultIndex + 2] = candidate->value;
			visitedVertices[currentVertexIndex] = true;
			pushReachableEdges();
			resultIndex++;
			i++;
		}
	}

	NeighborhoodList* result = new NeighborhoodList(vertexNumber - 1, vertexNumber, resultBuffor);
	delete[] resultBuffor;
	delete heap;
	return result;
}