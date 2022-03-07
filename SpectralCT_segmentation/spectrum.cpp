#include "spectrum.h"

namespace MXCT {

	float spectrum::interpolate_(float ener) {

		auto iter_high = std::find_if(data_.begin(), data_.end(),
			std::bind(&spectrum::greater_first_, std::placeholders::_1, ener));
		auto iter_low = iter_high;
		iter_low--;

		return linear_(ener, iter_low->first, iter_low->second, iter_high->first, iter_high->second);
	}

	float spectrum::linear_(float x, float x1, float x2, float y1, float y2) {
		return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
	}

	float spectrum::greater_first_(typename std::multimap<float, float>::value_type pair, float x) {
		return pair.first > x;
	}





	float spectrum::get_attenu(float ener) {
		return data_.find(ener) == data_.end() ? interpolate_(ener) : data_.lower_bound(ener)->second;
	}

	void spectrum::read_attenufile(std::string path) {

		//std::cout << "start reading attenuation data\n";

		std::ifstream* stream = new std::ifstream(path);
		std::string line;
		while (getline(*stream, line)) {
			std::vector<std::string> strs = MXCT::splitstring(line, ' ');
			data_.insert(std::pair<float, float>(stof(strs.at(0)) * 1000, stof(strs.at(1))));
			
			std::cout << "energy: " << stof(strs.at(0)) * 1000 << ", coeff: " << stof(strs.at(1)) << std::endl;
		}
	}
}