#pragma once

#include "Elements/Element.hpp"
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <list>
#include <memory>

using Eigen::MatrixXd;
using Eigen::VectorXd;

class Hg {
public:
  Hg(Element element, int size);
  VectorXd operator()(VectorXd &xk);

private:
  std::string m_elementType;
  int m_size;
  int m_negativeNode, m_positiveNode;
  int m_base, m_collector, m_emitter;
  int m_source, m_gate, m_drain;
};

VectorXd solveLinearCircuit(MatrixXd &A, VectorXd &b);

VectorXd newtonMethod(std::vector<Element> &nonlinearElements, int numNodes,
                      int numGroup2, MatrixXd &G, std::vector<Hg> &hg,
                      VectorXd &s, VectorXd &xk);

std::vector<Hg> getH_and_g(std::vector<Element> &nonlinearElements, int size);

VectorXd solveNonlinearCircuit(std::list<Element> &elements,
                               std::vector<Element> &nonlinearElements,
                               int numNodes, int numGroup2);

std::pair<std::vector<double>, std::vector<double>>
DCSweep(std::list<Element> &elements, std::vector<Element> &nonlinearElements,
        int numNodes, int numGroup2, int inputNode, double start, double end);
class Function {
public:
  Function(std::vector<Element> &nonlinearElements, std::vector<Hg> &hg,
           MatrixXd &G, VectorXd &s, int numNodes, int numGroup2) {
    m_Hg = hg;
    m_G = G;
    m_s = s;
    m_size = numNodes + numGroup2;
    m_nonlinearElements = nonlinearElements;
    m_numNodes = numNodes;
    m_numGroup2 = numGroup2;
  }

  double operator()(const std::vector<double> &x, std::vector<double> &grad);

  static double wrap(const std::vector<double> &x, std::vector<double> &grad,
                     void *data) {
    return (*reinterpret_cast<Function *>(data))(x, grad);
  }

private:
  std::vector<Hg> m_Hg;
  MatrixXd m_G;
  VectorXd m_s;
  int m_size;
  int m_numNodes;
  int m_numGroup2;
  std::vector<Element> m_nonlinearElements;
};
