#pragma once

#include "RawGraphData.h"

#include <random>

class Generator
{
public:
	static RawGraphData generate(float density, size_t vertexNumber, size_t maxValue = 10);
};