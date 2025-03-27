#include "stamp.hpp"
#include "Elements/Element.hpp"
#include <eigen3/Eigen/src/Core/ArithmeticSequence.h>
#include <numeric>
#include <utility>

std::pair<MatrixXd, VectorXd> stamp(std::list<Element>& elements, int numNodes, int numGroup2) {
	int currentsIndex = numNodes + 1;
	int size = numNodes + numGroup2 + 1;
	MatrixXd A(size, size);
	VectorXd rhs(size);
	for (auto& element : elements) {
		//resistor
		if (element.getName()[0] == 'R') {
			int positiveNode, negativeNode;
			positiveNode = element["positiveNode"]; negativeNode = element["negativeNode"];
			double g = 1 / element.getValue();
			//group 1
			if (element.getGroup() == Group::G1) {
				A(positiveNode, positiveNode) += g;
				A(negativeNode, negativeNode) += g;
				A(positiveNode, negativeNode) -= g;
				A(negativeNode, positiveNode) -= g;

			//group 2
			} else {
				A(positiveNode, currentsIndex) += 1;
				A(negativeNode, currentsIndex) -= 1;
				A(currentsIndex, positiveNode) += 1;
				A(currentsIndex, negativeNode) -= 1;
				A(currentsIndex, currentsIndex) -= element.getValue();
				currentsIndex++;
			}
		//current source
		} else if (element.getName()[0] == 'I') {
			int positiveNode, negativeNode;
			positiveNode = element["positiveNode"]; negativeNode = element["negativeNode"];
			double I = element.getValue();
			//group 1
			if (element.getGroup() == Group::G1) {
				rhs(positiveNode) = -I;
				rhs(negativeNode) = I;
			//group 2
			} else {
				A(positiveNode, currentsIndex) += 1;
				A(negativeNode, currentsIndex) -= 1;
				A(currentsIndex, currentsIndex) += 1;
				rhs(currentsIndex) = I;
				currentsIndex++;
			}
		//voltage source
		} else if (element.getName()[0] == 'V') {
			int positiveNode = element["positiveNode"]; int negativeNode = element["negativeNode"];
			A(positiveNode, currentsIndex) += 1;
			A(negativeNode, currentsIndex) -= 1;
			A(currentsIndex, positiveNode) += 1;
			A(currentsIndex, negativeNode) -= 1;
			rhs(currentsIndex) = element.getValue();
			currentsIndex++;
		}
	} 
	return std::make_pair(A(Eigen::lastN(size-1), Eigen::lastN(size-1)), rhs(Eigen::lastN(size-1)));
}
