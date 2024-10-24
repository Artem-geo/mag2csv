//
// Created by Artem on 2024-10-22.
//

#ifndef GEM_H
#define GEM_H
#include "Magnetometer.h"
#include <map>

using Coordinates = std::map<std::string, std::vector<std::string>>;

class GEM : public Magnetometer {
public:
    GEM() = default;
    GEM(Mag_input_params& input_params);
    ~GEM() = default;
    void save_to_csv() override;
private:
    Coordinates lat_lon_z;
    void open_file() override;
    static std::string parse_string_time(const std::string& time);
    static std::vector<std::string> parse_base_line(const std::string& line, char sep);
    static std::vector<std::string> parse_rover_line(const std::string&line, char sep);
};



#endif //GEM_H
