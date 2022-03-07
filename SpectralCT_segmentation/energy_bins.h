#pragma once
#include <map>
#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

namespace MXCT {
	struct single_bin {
		float begin, end;
	};

	class energy_bins {
	private:
		std::vector<single_bin> bininfo;
	public:
		energy_bins(){}

		void set_bin(float begin, float end) {
			single_bin bin = { begin, end };
			bininfo.push_back(bin);
		}

		int get_numof_bins() { return bininfo.size(); }
	};
}