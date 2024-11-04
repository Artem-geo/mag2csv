#ifndef MAGNETOMETER_H
#define MAGNETOMETER_H

#include <vector>
#include <string>
#include "Date.h"

enum class MagType {base, rover, none};
enum class MagMake {GEM, UNKNOWN};
struct MagInputParams {
    MagMake make {MagMake::UNKNOWN};
    MagType type {MagType::none};
    Date date {};
    std::string file_path;
    char sep {' '};
    MagInputParams() = default;
};

class Magnetometer {
public:
    Magnetometer() = default;
    Magnetometer(MagInputParams& input_params);
    virtual void openFile() {};
    virtual void saveToCSV() {};
    ~Magnetometer() = default;
protected:
    MagInputParams input_params;
    std::vector<std::string> readings;
    std::vector<std::string> times;
};



#endif //MAGNETOMETER_H
