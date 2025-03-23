#pragma once

#include <istream>
#include <list>
#include "Elements/Element.hpp"

std::pair<int,int> parse (std::istream& text, std::list<Element>& elements);
