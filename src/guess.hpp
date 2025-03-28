#pragma once

#include <eigen3/Eigen/Dense>
#include <list>
#include "Elements/Element.hpp"

using Eigen::VectorXd;
using Eigen::MatrixXd;

VectorXd getInitialGuess(std::list<Element>& elements, int size, int inputNodes);
