#include <fstream>
#include "Utils.h"
#include "GEM.h"


// int main(int argc, char* argv[])
int main() {
    int argc = 2;
    char* argv[2];
    std::string s1 = "mag2csv.exe";
    argv[0] = s1.data();
    std::string s2 = "C:/Dev/mag_data_transform/cpp/mag2csv/test/data/input.txt";
    argv[1] = s2.data();

    Mag_input_params input_params = Utils::parse_command_input_file(argc, argv);
    GEM mag {input_params};
    mag.save_to_csv();

    return 0;
}
