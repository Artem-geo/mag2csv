//
// 
//

#ifndef MAGNETOMETER_H
#define MAGNETOMETER_H

#include <vector>
#include <string>
#include "Date.h"

enum class Mag_type {base, rover, none};
enum class Mag_make {GEM, UNKNOWN};
struct Mag_input_params {
    Mag_make make {Mag_make::UNKNOWN};
    Mag_type type {Mag_type::none};
    Date date {};
    std::string file_path;
    char sep {' '};
    Mag_input_params() = default;
};

class Magnetometer {
public:
    Magnetometer() = default;
    Magnetometer(Mag_input_params& input_params);
    virtual void open_file() {};
    virtual void save_to_csv() {};
    ~Magnetometer() = default;
protected:
    Mag_input_params input_params;
    std::vector<std::string> readings;
    std::vector<std::string> times;
};



#endif //MAGNETOMETER_H
