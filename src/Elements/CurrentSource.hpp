#pragma once

#include "Element.hpp"

/*
* Current Source class inherits from Element
*/
class CurrentSource: public Element {
public:
	CurrentSource(std::string name, std::string positiveNode, std::string negativeNode, double value, Group group=Group::NO_GROUP):
	Element(name), m_positiveNode{positiveNode}, m_negativeNode{negativeNode}, m_value{value}, m_group{group} {}

	double getValue() { return m_value; }
	std::string getPositiveNode() { return m_positiveNode; }
	std::string getNegativeNode() { return m_negativeNode; }
	Group getGroup() { return m_group; }

private:
	std::string m_positiveNode;
	std::string m_negativeNode;
	double m_value;
	Group m_group;

};

