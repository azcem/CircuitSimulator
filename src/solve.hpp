#pragma once

#include <Eigen/Dense>
#include <Eigen/src/Core/Matrix.h>

using Eigen::MatrixXd;
using Eigen::VectorXd;

VectorXd solveLinearCircuit(MatrixXd &A, VectorXd &b);
