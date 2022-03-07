#include "util.h"
#include "multiCTimage.h"


void MXCT::multiCTimage::read_image(std::string inpath, int format_type, int width, int height) {

	if (format_type == format_raw && (width <= 0 || height <= 0)) {
		std::cerr << "width or height of the image is invalid.";
		return;
	}

	int count_bin = 0;
	int count_row = 0;
	int count_all = 0;

	for (const auto& file : std::filesystem::directory_iterator(inpath)) {
		std::cout << "reading: " << file.path() << std::endl;
		
		std::ifstream* stream;

		if (format_type == format_csv) {
			stream = new std::ifstream(file.path());
		}
		else {
			stream = new std::ifstream(file.path(), std::ios::binary);
		}
		
		std::string line;
		std::vector<std::vector<float>> tmp_singleimg;

		if (format_type == format_csv) {
			while (getline(*stream, line)) {
				std::vector<std::string> strs = MXCT::splitstring(line, ',');
				std::vector<float> tmp_line;
				for (int i = 0; i < strs.size(); i++) {

					tmp_line.push_back(stof(strs.at(i)));
					count_all++;
				}
				tmp_singleimg.push_back(tmp_line);
				count_row++;
			}
		}
		else if(format_type == format_raw){
			float buffer;
			for (int i = 0; i < height; i++) {
				std::vector<float> tmp_line;
				for (int j = 0; j < width; j++) {
					(*stream).read((char*)&buffer, sizeof(float));
					tmp_line.push_back(buffer);
					count_all++;
				}
				tmp_singleimg.push_back(tmp_line);
				count_row++;
			}
		}
		
		img.push_back(tmp_singleimg);
		count_bin++;

		delete stream;
	}

	std::cout << count_all / count_row << ", " << count_row << std::endl;

	img_width = count_all / count_row;
	img_height = count_row / count_bin;
	img_bins = count_bin;
}




void MXCT::multiCTimage::write_image(std::string outpath, int format_type) {


	for (int bin = 0; bin < img_bins; bin++) {
		std::string _outpath = outpath + "\\bin";
		_outpath += std::to_string(bin) + ".csv";

		std::ofstream stream(_outpath);

		for (int row = 0; row < img_height; row++) {
			for (int col = 0; col < img_width; col++) {
				stream << img[bin][row][col] << ",";
			}
			stream << '\b' << std::endl;
		}
	}
}


