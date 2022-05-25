#pragma once

#include "IncidentMatrix.h"
#include "NeighborhoodList.h"
#include "Edge.h"

class Prim
{
	static IncidentMatrix* generateMst(IncidentMatrix* incidentMatrix);
	static NeighborhoodList* generateMst(NeighborhoodList* neighborhoodList);
};