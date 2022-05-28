#pragma once

#include "IncidentMatrix.h"
#include "NeighborhoodList.h"

class Reader
{
public:
	IncidentMatrix* readMatrix(std::string);
	NeighborhoodList* readList(std::string);
};