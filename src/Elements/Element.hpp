#pragma once

#include <string>

/* Enum for optional group clause */
enum class Group {
	NO_GROUP,
	G2
};

/* default value if one is not provided (for nonlinear devices) */
#define NO_VALUE -1

/*
* Base class for element devices.
*/
class Element {
public:
	Element(std::string& name): m_name{name} {};
	void setName(std::string& name) { m_name = name; }
	std::string getName() { return m_name; }
private:
	std::string m_name;
};
