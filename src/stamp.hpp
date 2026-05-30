#pragma once

#include "Elements/Element.hpp"
#include <Eigen/Dense>
#include <Eigen/src/Core/Matrix.h>
#include <list>

using Eigen::MatrixXd;
using Eigen::VectorXd;

std::pair<MatrixXd, VectorXd> stamp(std::list<Element> &elements, int numNodes,
                                    int numGroup2);
