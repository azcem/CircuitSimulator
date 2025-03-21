#pragma once

#include "Element.hpp"

/*
* Voltage Source class inherits from Element
*/
class VoltageSource : public Element {
public:
	VoltageSource(std::string name, std::string positiveNode, std::string negativeNode, double value):
	Element(name), m_positiveNode{positiveNode}, m_negativeNode{negativeNode}, m_value{value} {}

	double getValue() { return m_value; }
	std::string getPositiveNode() { return m_positiveNode; }
	std::string getNegativeNode() { return m_negativeNode; }

private:
	std::string m_positiveNode;
	std::string m_negativeNode;
	double m_value;

};
