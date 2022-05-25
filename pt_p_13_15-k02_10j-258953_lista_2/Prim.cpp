#include "Prim.h"

using namespace std;

IncidentMatrix * Prim::generateMst(IncidentMatrix * incidentMatrix)
{
	size_t vertexNumber = incidentMatrix->getVertexNumber();
	size_t edgeNumber = incidentMatrix->getEdgeNumber();
	size_t* values = incidentMatrix->getValues();
	CellType** matrix = incidentMatrix->getMatrix();
	return nullptr;
}

NeighborhoodList * Prim::generateMst(NeighborhoodList * neighborhoodList)
{
	return nullptr;
}