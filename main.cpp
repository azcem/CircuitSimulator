#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <format>
#include <ranges>
#include "src/stamp.hpp"
#include "src/solve.hpp"
#include "src/parse.hpp"

std::string printValues(std::list<Element>& elements, VectorXd x, int numNodes, int numGroup2) {
	std::string result;
	int i = 0;
	for (; i < numNodes; i++) {
		result += std::format("V({}) = {}", i+1, x(i));
		result += '\n';
	}
	auto view = elements | std::views::filter([] (auto element) {return element.getGroup() == Group::G2;});
	for (auto element : view) {
		result += std::format("I({}) = {}", element.getName(), x(i++));
		result += '\n';
	}
	return result;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "please enter circuit description file\n";
		return 1;
	}
	std::filesystem::path filepath {argv[1]};
	std::ifstream ifile { filepath };
	std::list<Element> elements;
	auto [numNodes, numGroup2] = parse(ifile, elements);

	auto [A, rhs] = stamp(elements, numNodes, numGroup2);

	VectorXd x = solveLinearCircuit(A, rhs);
	std::cout << printValues(elements, x, numNodes, numGroup2);
}
