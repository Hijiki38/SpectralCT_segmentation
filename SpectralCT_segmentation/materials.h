#pragma once
#include<map>
#include<algorithm>
#include<functional>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <assert.h>
#include "util.h"
#include "spectrum.h"

namespace MXCT {

	struct single_material {
		std::string name;
		float density;
		MXCT::spectrum attenu;
	};

	class materials {
	private:
		std::vector<single_material> mat_list;

	public:
		materials(){}

		materials(std::string inpath) {
			read_materials(inpath);
		}

		void read_materials(std::string inpath) {
			for (const auto& file : std::filesystem::directory_iterator(inpath)) {

				std::string materialname, filename;
				std::vector<std::string> splited_filename;
				MXCT::spectrum coeff;
				float dens;

				filename = file.path().stem().string();
				splited_filename = splitstring(filename, '_');
				assert(splited_filename.size() == 2);
				materialname = splited_filename[0];
				dens = stof(splited_filename[1]);

				std::cout << "registering " << materialname << std::endl;
				coeff.read_attenufile(file.path().string());

				single_material mat = { materialname, dens, coeff };
				mat_list.push_back(mat);

			}
		}

		std::vector<single_material> get_matlist() { return mat_list; }
	};
}