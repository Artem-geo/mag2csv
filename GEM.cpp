#include "GEM.h"
#include "fstream"
#include "sstream"
#include <iostream>
#include "Utils.h"
#include <algorithm>

GEM::GEM(Mag_input_params &input_params)
     : Magnetometer(input_params) {
    // lat_lon_z is initialised for rover only
    if (input_params.type == Mag_type::rover) {
        lat_lon_z = {{"lat", {}},
                        {"lon", {}},
                        {"z", {}}};
    }
    open_file();
 }
/**
* @brief Parses base file from the provided path
* @param filepath path to the base file
* @return Magnetometer object with all object members filled
*/
void GEM::open_file() {
    std::ifstream ifile;
    ifile.open(input_params.file_path);
    if (!ifile.is_open())
        throw std::ios_base::failure{"Can't open the file in the directory " + input_params.file_path};
    std::string line;
    std::vector<std::string> values; // vector containing values extracted from a file
    while(std::getline(ifile, line)) {
        if (line.size()<2 || line[0]=='/') continue;
        if (input_params.type == Mag_type::base) {
            values = parse_base_line(line, input_params.sep);
            times.push_back(values[0]);
            readings.push_back(values[1]);
        }
        if (input_params.type == Mag_type::rover) {
            values = parse_rover_line(line, input_params.sep);
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
std::vector<std::string> GEM::parse_rover_line(const std::string &line, char sep) {
    std::vector<std::string> tokens;
    std::stringstream ss {line};
    std::string token;
    while(std::getline(ss, token, sep)) {
        if (token.size()<2) continue;
        tokens.push_back(token);
    }
    return tokens;
}
std::vector<std::string> GEM::parse_base_line(const std::string& line, const char sep) {
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
std::string GEM::parse_string_time(const std::string& time) {
    return time.substr(0,2) + ":" + time.substr(2,2) + ":" + time.substr(4,time.size()-4);
}
void GEM::save_to_csv() {
    int dot_char = input_params.file_path.find_last_of('.');
    std::string output_filepath = input_params.file_path.substr(0, dot_char) + ".csv";
    std::ofstream ofile (output_filepath, std::ios::trunc);
    if (input_params.type==Mag_type::base) ofile << "DATE,TIME,BASE\n";
    if (input_params.type==Mag_type::rover) ofile << "DATE,TIME,TMI,LAT,LON,Z\n";

    for (size_t i{0}; i<readings.size(); ++i) {
        ofile << input_params.date.toString() << ",";
        ofile << parse_string_time(times[i]) << "," << readings[i];
        if (input_params.type==Mag_type::rover) {
            ofile << "," << lat_lon_z["lat"][i] << "," << lat_lon_z["lon"][i] << "," << lat_lon_z["z"][i];
        }
        ofile << "\n";
    }
    ofile.close();
}