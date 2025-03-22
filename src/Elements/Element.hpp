#pragma once

#include <string>
#include <unordered_map>

/* Enum for optional group clause */
enum class Group {
	G1,
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
	std::string getName() const { return m_name; }
	void setValue(double value) { m_value = value; }
	double getValue() const { return m_value; }
	auto& operator[](const std::string& key) { return m_nodes[key]; }
	Group getGroup() const { return m_group; }
	void setGroup(Group group) { m_group = group; }

private:
	std::string m_name;
	double m_value;
	std::unordered_map<std::string, int> m_nodes;
	Group m_group = Group::G1;
};
