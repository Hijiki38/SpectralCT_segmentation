#include "util.h"


std::vector<std::string> MXCT::splitstring(std::string& input, char delimiter) {
	std::istringstream stream(input);
	std::string field;
	std::vector<std::string> output;

	while (getline(stream, field, delimiter)) {
		output.push_back(field);
	}

	return output;
}
