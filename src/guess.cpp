#include "guess.hpp"
#include "stamp.hpp"
#include "constants.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>

void stepSources(std::list<Element>& sources) {
	std::for_each(sources.begin(), sources.end(), [] (Element& element) {
		if (element.getValue() + STEP > element.getOriginalValue()) {
			element.setValue(element.getOriginalValue());
		} else {
			element.setValue(element.getValue() + STEP);
		}
	       });
}



VectorXd getInitialGuess(std::list<Element> &elements, int numNodes, int numGroup2, int inputNode) {
	auto sources = elements 
		| std::views::filter([] (auto& element) {return INDEPENDENT_SOURCES.count(element.getName()[0]) == 1;});

	double maxVal = 0;
	std::ranges::for_each(sources, [&maxVal](auto& element) { maxVal = std::max(maxVal, element.getValue()); element.setValue(0);});
	for (auto element : elements) {
		std::cout << element << '\n';
	}
	auto [G, s] = stamp(elements, numNodes, numGroup2);
}
