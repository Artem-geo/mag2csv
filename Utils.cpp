//
// Created by Artem on 2024-10-15.
//

#include <fstream>
#include <iostream>
#include "Utils.h"

/**
* @brief parses the command input
* @param argc number of passed arguments
* @param argv vector of strings containing the arguments
* @return MagInputParam object
*/
Mag_input_params Utils::parse_command_input_file(const int argc, char* argv[]) {
    Mag_input_params input_params{};
    if(argc!=2) { // two input arguments argc and argv
        std::cerr << "Wrong number of specified arguments" << std::endl;
        std::cerr << "Specified: " << argc << " Needed: 2" << std::endl;
        std::terminate();
    }
    std::ifstream ifile;
    ifile.open(argv[1]);
    if (!ifile.is_open()) {
        std::cerr << "The file can't be opened" << std::endl;
        std::terminate();
    }
    std::vector<std::string> parameters;
    std::string parameter;
    while (std::getline(ifile, parameter)) {
        if (parameter[0] == '/') continue; // skip comment lines from input file
        parameters.push_back(parameter);
    }
    try {
        input_params.make = parse_mag_make(parameters[0]);
        input_params.type = parse_mag_type(parameters[1]);
        input_params.sep = parse_separator(parameters[2]);
        input_params.date = parse_date_format(parameters[3]);
        input_params.file_path = parameters[4];
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        std::terminate();
    }
    return input_params;
}

/**
 * 
 * @param mag_make magnetometer manufacturer (0-GEM)
 * @return Mag_make enum class object
 */
Mag_make Utils::parse_mag_make(const std::string& mag_make) {
    switch (std::stoi(mag_make)) {
        case 0: return Mag_make::GEM;
        case 1: return Mag_make::UNKNOWN;
        default: throw std::invalid_argument("Invalid magnetometer type");
    }
}
/**
 * @brief Checks magnetometer type
 * @param mag_type string representation of the magnetometer reading type
 * @return mag_type = 0 -> MagType::base
 * @return mag_type = 1 -> MagType::rover
 * @return mag_type = something else -> throws exception
 */
Mag_type Utils::parse_mag_type(const std::string& mag_type) {
    switch (std::stoi(mag_type)) {
        case 0: return Mag_type::base;
        case 1: return Mag_type::rover;
        default: throw std::invalid_argument("Invalid magnetometer type");
    }
}
/**
* @brief Checks user-provided date
* @param input_date date string in the format -d=YYYY-MM-DD
* @return date object
* @return throws exceptions if input_date size != 13 || invalid numeric values
*/
Date Utils::parse_date_format(const std::string& input_date) {
    Date date{};
    try {
        if (input_date.size()!=10) throw std::invalid_argument("Check date parameter");
        date.setYear(std::stoi(input_date.substr(0, 4)));
        date.setMonth(std::stoi(input_date.substr(5, 2)));
        date.setDay(std::stoi(input_date.substr(8, 2)));
    } catch (const std::exception& e) {
        throw;
    }
    return date;
}
/**
 * @brief parses input parameter corresponding to the file separator
 * @param input_separator numeric value for a separator (0-comma, 1-space, 2-colon)
 * @return char separator
 */
char Utils::parse_separator(const std::string &input_separator) {
    switch (std::stoi(input_separator)) {
        case 0: return ',';
        case 1: return ' ';
        case 2: return ':';
        default: throw std::invalid_argument("Unknown separator");
    }
}









