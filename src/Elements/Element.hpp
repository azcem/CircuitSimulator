#pragma once

#include <string>
#include <unordered_map>
#include <format>

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
	void setOriginalValue(double value) { m_originalValue = value; }
	double getOriginalValue() const { return m_originalValue; }
	double getValue() const { return m_value; }
	auto& operator[](const std::string& key) { return m_nodes[key]; }
	Group getGroup() const { return m_group; }
	void setGroup(Group group) { m_group = group; }
	friend std::ostream &operator<<(std::ostream &str, const Element& element);


private:
	std::string m_name;
	double m_value;
	std::unordered_map<std::string, int> m_nodes;
	Group m_group = Group::G1;
	double m_originalValue;
};

