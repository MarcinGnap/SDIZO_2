#pragma once

//	Niepotrzebne?

#include "CellType.h"
#include <cstdlib>

struct MatrixCell
{
	CellType type;
	size_t weight;

	MatrixCell() : type{ CellType::empty }, weight{ 0 }
	{}
	MatrixCell(CellType type, const size_t &weight) : type{ type }, weight{ weight }
	{};
};