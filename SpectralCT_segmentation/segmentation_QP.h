#pragma once
#include<map>
#include<algorithm>
#include<functional>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "multiCTimage.h"
#include "materials.h"

namespace MXCT {
	class segmentation_QP {
	private:
	public:
		static std::map<std::string, std::vector<std::vector<float>>> segmentation_qp(MXCT::multiCTimage inimgs, MXCT::materials materials, std::vector<float> mean_energies){ //, MXCT::spectrum tube_spectrum, MXCT::spectrum detector_spectrum) {

			std::vector<std::vector<std::vector<float>>> img = inimgs.get_image();
			std::vector<std::vector<std::vector<float>>> coeff; // all 1?
			//MXCT::spectrum bg_spectrum = tube_spectrum * detector_spectrum;
			std::map<std::string, std::vector<std::vector<float>>> outimg;
			//std::vector<std::vector<std::vector<float>>> outimg = inimgs.get_image();


			for (const auto& mat : materials.get_matlist()) {
				std::vector<std::vector<float>> tmp_;
				tmp_.assign(inimgs.get_height(), std::vector<float>(inimgs.get_width(), 0)); //Initialize
				outimg.insert(std::pair<std::string, std::vector<std::vector<float>>>(mat.name, tmp_));
			}

			for (int h = 0; h < inimgs.get_height(); h++) {
				for (int w = 0; w < inimgs.get_width(); w++) {
					float min_error = FLT_MAX;
					MXCT::single_material min_material;
					for (const auto& mat : materials.get_matlist()) {
						float error = 0;
						spectrum ac = mat.attenu;
						MXCT::energy_bins enerbins = inimgs.get_bins();

						for (int b = 0; b < enerbins.get_numof_bins(); b++) {
							//float mean_energy = bg_spectrum.get_w_average(enerbins, b);
							float mean_energy = mean_energies[b];
							float tmp = img[b][h][w] - coeff[b][h][w] * ac.get_attenu(mean_energy) * mat.density;
							error += std::pow(tmp, 2);
						}
						if (error < min_error) {
							min_error = error;
							min_material = mat;
						}
					}

					auto itr = outimg.find(min_material.name);
					if (itr != outimg.end()) {
						itr->second[h][w] = 1;
					}

				}
			}

			return outimg;
		}
	};
}