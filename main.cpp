#include "src/guess.hpp"
#include "src/parse.hpp"
#include "src/solve.hpp"
#include "src/stamp.hpp"
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <filesystem>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <nlopt.hpp>
#include <numeric>
#include <ranges>

std::string printValues(std::list<Element> &elements, VectorXd x, int numNodes,
                        int numGroup2) {
  std::string result;
  int i = 0;
  for (; i < numNodes; i++) {
    result += std::format("V({}) = {}", i + 1, x(i));
    result += '\n';
  }
  auto view = elements | std::views::filter([](auto element) {
                return element.getGroup() == Group::G2;
              });
  for (auto element : view) {
    result += std::format("I({}) = {}", element.getName(), x(i++));
    result += '\n';
  }
  return result;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "please enter circuit description file\n";
    return 1;
  }
  std::filesystem::path filepath{argv[1]};
  std::ifstream ifile{filepath};
  std::list<Element> elements;
  std::vector<Element> nonlinearElements;
  std::vector<Element> dynamicElements;
  auto [numNodes, numGroup2] =
      parse(ifile, elements, nonlinearElements, dynamicElements);

  auto [in, out] =
      DCSweep(elements, nonlinearElements, numNodes, numGroup2, 1, 0, 3);
  for (auto val : out) {
    std::cout << val << std::endl;
  }
}
