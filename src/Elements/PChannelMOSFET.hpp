#pragma once

#include "Element.hpp"

/*
* P-channel MOSFET Transistor class inherits from Element
*/
class PChannelMOSFET: public Element {
public:
	PChannelMOSFET(std::string name, std::string drainNode, std::string gateNode, std::string sourceNode, double value=NO_VALUE):
	Element(name), m_drainNode{drainNode}, m_gateNode{gateNode}, m_sourceNode{sourceNode}, m_value{value} {}

	double getValue() { return m_value; }
	std::string getDrainNode() { return m_drainNode;}
	std::string getGateNode() { return m_gateNode; }
	std::string getSourceNode() { return m_sourceNode; }

private:
	std::string m_drainNode;
	std::string m_gateNode;
	std::string m_sourceNode;
	double m_value;

};
