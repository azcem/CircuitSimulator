#include "src/parse.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include "src/stamp.hpp"

int main() {
	std::filesystem::path filepath {"./test.circuit"};
	std::ifstream ifile { filepath };
	std::list<Element> elements;
	auto [numNodes, numGroup2] = parse(ifile, elements);
	for (auto& element : elements) {
		std::cout << element;
	}

	/*MatrixXd A(numNodes+numGroup2+1, numNodes+numGroup2+1);*/
	/*VectorXd rhs(numNodes+numGroup2+1);*/
	auto [A, rhs] = stamp(elements, numNodes, numGroup2);
	std::vector<int> indices (numNodes+numGroup2);
	std::iota(indices.begin(), indices.end(), 1);
	auto A_modified = A(indices, indices);

	std::cout << A;
	std::cout << rhs << std::endl;
	std::cout <<std::endl;
	std::cout << A.determinant();
}
