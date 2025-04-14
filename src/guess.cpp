#include "guess.hpp"
#include "solve.hpp"
#include "stamp.hpp"
#include "constants.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>

void stepSources(auto& sources) {
	std::ranges::for_each(sources, [] (Element& element) {
		if (element.getValue() + STEP > element.getOriginalValue()) {
			element.setValue(element.getOriginalValue());
		} else {
			element.setValue(element.getValue() + STEP);
		}
	       });
}



VectorXd getInitialGuess(std::list<Element> &elements, std::vector<Element>& nonlinearElements, int numNodes, int numGroup2) {
	auto sources = elements 
		| std::views::filter([] (auto& element) {return INDEPENDENT_SOURCES.count(element.getName()[0]) == 1;});

	double maxVal = 0;
	std::ranges::for_each(sources, [&maxVal](auto& element) { maxVal = std::max(maxVal, element.getValue()); element.setValue(0);});
	VectorXd xk = VectorXd::Random(numNodes+numGroup2);
	for (int i = 0; i < maxVal/STEP + 1; i++) {
		stepSources(sources);
		auto [G, s] = stamp(elements, numNodes, numGroup2);
		auto hg = getH_and_g(nonlinearElements, numNodes+numGroup2);
		xk = newtonMethod(nonlinearElements, numNodes, numGroup2, G, hg, s, xk);
	}
	return xk;
}
