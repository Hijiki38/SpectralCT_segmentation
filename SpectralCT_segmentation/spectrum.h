#pragma once
#include<map>
#include<algorithm>
#include<functional>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "util.h"


namespace MXCT {
	class spectrum {
	private:
		std::multimap<float, float> data_;  // energy, attenu

		float interpolate_(float ener);

		float linear_(float x, float x1, float x2, float y1, float y2);

		static float greater_first_(typename std::multimap<float, float>::value_type pair, float x);

	public:
		spectrum(){}

		spectrum operator * (spectrum sp) {
			spectrum result = *(new spectrum());
			for (const auto& data : this->data_) {
				// TODO: �X�y�N�g�����m�̐ς�����.�@���}����g����D�@�Е��ł̃L�[���Ԃ�͂悢���C�����ł̃L�[���͂͂����D
				//result.data_.
			}
		}

		float get_attenu(float ener);

		void read_attenufile(std::string path);
	};
}