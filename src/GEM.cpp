#include "GEM.h"
#include "fstream"
#include "sstream"
#include <iostream>
#include "Utils.h"
#include <algorithm>

GEM::GEM(MagInputParams &input_params)
     : Magnetometer(input_params) {
    // lat_lon_z is initialised for rover only
    if (input_params.type == MagType::rover) {
        lat_lon_z = {{"lat", {}},
                        {"lon", {}},
                        {"z", {}}};
    }
    openFile();
 }
/**
* @brief Parses base file from the provided path
* @param filepath path to the base file
* @return Magnetometer object with all object members filled
*/
void GEM::openFile() {
    std::ifstream ifile;
    ifile.open(input_params.file_path);
    if (!ifile.is_open())
        throw std::ios_base::failure{"Can't open the file in the directory " + input_params.file_path};
    std::string line;
    std::vector<std::string> values; // vector containing values extracted from a file
    while(std::getline(ifile, line)) {
        if (line.size()<2 || line[0]=='/') continue;
        if (input_params.type == MagType::base) {
            values = parseBaseLine(line, input_params.sep);
            times.push_back(values[0]);
            readings.push_back(values[1]);
        }
        if (input_params.type == MagType::rover) {
            values = parseRoverLine(line, input_params.sep);
            // std::cout << values[0] << " | " << values[1] << " | " << values[4] << " | ";
            // std::cout << values[9] << " | " << values[5] << std::endl;
            times.push_back(values[9]);
            readings.push_back(values[5]);
            lat_lon_z["lat"].push_back(values[0]);
            lat_lon_z["lon"].push_back(values[1]);
            lat_lon_z["z"].push_back((values[4]));
        }
    }
    ifile.close();
}
std::vector<std::string> GEM::parseRoverLine(const std::string &line, char sep) {
    std::vector<std::string> tokens;
    std::stringstream ss {line};
    std::string token;
    while(std::getline(ss, token, sep)) {
        if (token.size()<2) continue;
        tokens.push_back(token);
    }
    return tokens;
}
std::vector<std::string> GEM::parseBaseLine(const std::string& line, const char sep) {
    std::vector<std::string> tokens;
    std::stringstream ss {line};
    std::string token;
    std::vector<std::string> time_field;
    while(std::getline(ss, token, sep)) {
        if (token.size()<2) continue;
        tokens.push_back(token);
    }
    try {
        time_field.push_back(tokens[0]);
        time_field.push_back(tokens[1]);
    } catch (const std::exception& e) {
        throw;
    }
    return time_field;
}
std::string GEM::parseStringTime(const std::string& time) {
    return time.substr(0,2) + ":" + time.substr(2,2) + ":" + time.substr(4,time.size()-4);
}
void GEM::saveToCSV() {
    int dot_char = input_params.file_path.find_last_of('.');
    std::string output_filepath = input_params.file_path.substr(0, dot_char) + ".csv";
    std::ofstream ofile (output_filepath, std::ios::trunc);
    if (input_params.type==MagType::base) ofile << "DATE,TIME,BASE\n";
    if (input_params.type==MagType::rover) ofile << "DATE,TIME,TMI,LAT,LON,Z\n";

    for (size_t i{0}; i<readings.size(); ++i) {
        ofile << input_params.date.toString() << ",";
        ofile << parseStringTime(times[i]) << "," << readings[i];
        if (input_params.type==MagType::rover) {
            ofile << "," << lat_lon_z["lat"][i] << "," << lat_lon_z["lon"][i] << "," << lat_lon_z["z"][i];
        }
        ofile << "\n";
    }
    ofile.close();
}