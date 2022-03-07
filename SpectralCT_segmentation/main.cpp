#include "util.h"
#include "multiCTimage.h"
#include "materials.h"
#include "segmentation_QP.h"

int main(int argc, char* argv[]) {

	//std::string inpath = "C:\\Users\\takum\\Dropbox\\Aoki_Lab\\simulation\\egs\\lineCTmpi\\result\\result20211104fourtissues_45missing\\rec\\10bins\\csv";
	std::string inpath = "D:\\tmp\\postprocessingsegmentation\\testinput\\fourmetal_z43";
	std::string matpath = "D:\\tmp\\postprocessingsegmentation\\material";
	std::string outpath = "D:\\tmp\\postprocessingsegmentation";

	MXCT::multiCTimage img(inpath, MXCT::format_raw, 2048, 2048);
	std::map<std::string, std::vector<std::vector<float>>> outimgs;
	MXCT::materials materials;

	materials.read_materials(matpath);

	outimgs = MXCT::segmentation_QP::segmentation_qp(img, materials);


	//outimgs.write_image(outpath, MXCT::format_raw);


	

}
