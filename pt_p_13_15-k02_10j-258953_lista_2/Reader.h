#pragma once

#include "IncidentMatrix.h"
#include "NeighborhoodList.h"

#include <iostream>
#include <fstream>
#include <tuple>

class Reader
{
public:
	Reader(std::string basePath);

	IncidentMatrix* readMatrixGraph(std::string fileName);
	NeighborhoodList* readListGraph(std::string fileName);

private:
	std::string basePath;

	std::tuple<size_t, size_t, size_t*> readData(std::string fileName);
};