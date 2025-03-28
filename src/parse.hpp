#pragma once

#include <istream>
#include <list>
#include <vector>
#include "Elements/Element.hpp"

std::pair<int,int> parse (std::istream& text, std::list<Element>& elements, std::vector<Element>& nonlinearElements, std::vector<Element>& dynamicElements);
