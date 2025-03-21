#pragma once

#include "Element.hpp"

/*
* NPN Transistor class inherits from Element
*/
class NPNBJT: public Element {
public:
	NPNBJT(std::string name, std::string collectorNode, std::string baseNode, std::string emitterNode, double value=NO_VALUE):
	Element(name), m_collectorNode{collectorNode}, m_baseNode{baseNode}, m_emitterNode{emitterNode}, m_value{value} {}

	double getValue() { return m_value; }
	std::string getCollectorNode() { return m_collectorNode;}
	std::string getBaseNode() { return m_baseNode; }
	std::string getEmitterNode() { return m_emitterNode; }

private:
	std::string m_collectorNode;
	std::string m_baseNode;
	std::string m_emitterNode;
	double m_value;

};

