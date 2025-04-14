#pragma once

#include <eigen3/Eigen/Dense>
#include <list>
#include "Elements/Element.hpp"

using Eigen::VectorXd;
using Eigen::MatrixXd;

VectorXd getInitialGuess(std::list<Element> &elements, std::vector<Element>& nonlinearElements, int numNodes, int numGroup2);
