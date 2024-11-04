#include <fstream>
#include "Utils.h"
#include "GEM.h"


// int main(int argc, char* argv[])
int main() {
    int argc = 2;
    char* argv[2];
    std::string s1 = "mag2csv.exe";
    argv[0] = s1.data();
    std::string s2 = "C:/Dev/mag_data_transform/cpp/mag2csv/test/input.txt";
    argv[1] = s2.data();

    MagInputParams input_params = Utils::parseCommandInputFile(argc, argv);
    GEM mag {input_params};
    mag.saveToCSV();

    return 0;
}
