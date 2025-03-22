#include "parse.hpp"
#include "Elements/Element.hpp"
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> getTokens(std::istream& line) {
	std::vector<std::string> result;
	std::string token;
	while (line >> token) {
		if (token[0] == '%')
			break;
		result.push_back(token);
	}
	return result;
}

std::list<Element> parse(std::istream& text) {
	std::list<Element> elements;
	std::string line;
	std::vector<char> twoTerminalDevices {'V', 'I', 'R', 'C', 'I', 'D'};
	while (std::getline(text, line)) {
		std::istringstream lineStream {line};
		auto tokens = getTokens(lineStream);
		if (tokens.size() == 0) continue;
		auto elementName = tokens[0];
		Group group = Group::G1;
		//Voltage sources are automaticallly in group 2
		if (tokens.size() == 5 || elementName[0] == 'V') {
			group = Group::G2;
		}

		if (std::find(twoTerminalDevices.cbegin(), twoTerminalDevices.cend(), elementName[0]) != twoTerminalDevices.cend()) {
			Element element{elementName};
			if (tokens.size() >= 4) {
				element.setValue(std::stod(tokens[3]));
			}
			element["positiveNode"] = std::stoi(tokens[1]);
			element["negativeNode"] = std::stoi(tokens[2]);
			element.setGroup(group);
			elements.push_back(element);

		//BJT
		} else if (elementName[0] == 'Q') {
			Element element{elementName};
			if (tokens.size() == 5) {
				element.setValue(std::stod(tokens[4]));
			}
			element["collector"] = std::stoi(tokens[1]);
			element["base"] = std::stoi(tokens[2]);
			element["emitter"] = std::stoi(tokens[3]);
			elements.push_back(element);

		//MOSFET
		} else if (elementName[0] == 'M') {
			Element element{elementName};
			if (tokens.size() == 5) {
				element.setValue(std::stod(tokens[4]));
			}
			element["drain"] = std::stoi(tokens[1]);
			element["gate"] = std::stoi(tokens[2]);
			element["source"] = std::stoi(tokens[3]);
			elements.push_back(element);
		}
	}
	return elements;
}
