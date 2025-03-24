#include "solve.hpp"


VectorXd solveLinearCircuit(MatrixXd& A, VectorXd& b) {
	return A.partialPivLu().solve(b);
}
