#include "Version.h"
#include <fstream>

void WriteVersionInfo() {
	std::ofstream ofs("version.txt");
	ofs << VERSION_STRING << std::endl;
	ofs.close();
}
