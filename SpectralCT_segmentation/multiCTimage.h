#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "util.h"
#include "energy_bins.h"


namespace MXCT {

	enum file_format {
		format_raw,
		format_csv,
	};

	class multiCTimage {
	private:
		int img_width;
		int img_height;
		MXCT::energy_bins bins;

		std::vector<std::vector<std::vector<float>>> img;

	public:
		multiCTimage(){}

		multiCTimage(std::string inpath, int format) {
			read_image(inpath, format);
		}

		multiCTimage(std::string inpath, int format, int width, int height) {
			read_image(inpath, format, width, height);
		}


		void read_image(std::string inpath, int format_type, int width = -1, int height = -1);

		void write_image(std::string inpath, int format_type);

		std::vector<std::vector<std::vector<float>>> get_image() { return img; }

		int get_width() { return img_width; }

		int get_height() { return img_height; }

		MXCT::energy_bins get_bins() { return bins; }

	};
}