#pragma once

#include "Element.hpp"

/*
* Inductor class inherits from Element
*/
class Inductor: public Element {
public:
	Inductor(std::string name, std::string positiveNode, std::string negativeNode, double value, Group group=Group::NO_GROUP):
	Element(name), m_positiveNode{positiveNode}, m_negativeNode{negativeNode}, m_value{value}, m_group{group} {}

	double getValue() { return m_value; }
	std::string getPositiveNode() { return m_positiveNode; }
	std::string getNegativeNode() { return m_negativeNode; }

private:
	std::string m_positiveNode;
	std::string m_negativeNode;
	double m_value;
	Group m_group;

};


