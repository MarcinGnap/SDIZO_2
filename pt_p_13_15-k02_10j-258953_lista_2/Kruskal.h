#pragma once

#include "IncidentMatrix.h"
#include "NeighborhoodList.h"
#include "EdgeHeap.h"

class Kruskal
{
public:
	static IncidentMatrix* generateMst(IncidentMatrix* incidentMatrix);
	static NeighborhoodList* generateMst(NeighborhoodList* neighborhoodList);
};