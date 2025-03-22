#pragma once

#include <istream>
#include <list>
#include <memory>
#include <string>
#include "Elements/Element.hpp"

std::list<Element> parse (std::istream& text);
