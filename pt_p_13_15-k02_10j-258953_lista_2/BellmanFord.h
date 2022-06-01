#pragma once

#include "IncidentMatrix.h"
#include "NeighborhoodList.h"
#include "Path.h"
#include "PathEdge.h"

class BellmanFord
{
public:
	static Path findShortestPath(IncidentMatrix* incidentMatrix, size_t from, size_t to);
	static Path findShortestPath(NeighborhoodList* neighborhoodList, size_t from, size_t to);
};