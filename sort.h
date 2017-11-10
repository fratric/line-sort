#pragma once

#include <fstream>
#include <ostream>

#include "defs.h"

namespace sort
{
	bool process(Order order, Filter filter, Case compare, FilterSpace space, std::istream & input, std::ostream & output);
}

