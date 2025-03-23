#include "Element.hpp"
#include <ostream>

std::ostream &operator<<(std::ostream &str, const Element& element) {
  str << std::format("{} {}", element.m_name, element.m_value);
  for (auto it = element.m_nodes.cbegin(); it != element.m_nodes.cend(); ++it) {
    str << std::format(" {} {}", it->first, it->second);
  }
  str << std::endl;
  return str;
}

