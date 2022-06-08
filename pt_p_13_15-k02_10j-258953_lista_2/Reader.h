#pragma once

#include "IncidentMatrix.h"
#include "NeighborhoodList.h"

#include <iostream>
#include <fstream>
#include <tuple>

class Reader
{
public:
	IncidentMatrix* readerForMatrix(std::string);
	NeighborhoodList* readerForList(std::string);
};