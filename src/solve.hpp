#pragma once

#include "Elements/Element.hpp"
#include <eigen3/Eigen/Dense>
#include <list>

using Eigen::MatrixXd;
using Eigen::VectorXd;

class Hg{
public:
	Hg(Element element, int size);
	VectorXd operator()(VectorXd& xk);
private:
	std::string m_elementType;
	int m_size;
	int m_negativeNode, m_positiveNode;
	int m_base, m_collector, m_emitter;
	int m_source, m_gate, m_drain;
};


VectorXd solveLinearCircuit(MatrixXd& A, VectorXd& b);

VectorXd newtonMethod(std::list<Element>& nonLinearElements, int numNodes, int numGroup2, MatrixXd& G, std::vector<Hg>& hg, VectorXd& s, VectorXd& xk);
