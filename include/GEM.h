#ifndef GEM_H
#define GEM_H
#include "Magnetometer.h"
#include <map>

using Coordinates = std::map<std::string, std::vector<std::string>>;

class GEM : public Magnetometer {
public:
    GEM() = default;
    GEM(MagInputParams& input_params);
    ~GEM() = default;
    void saveToCSV() override;
private:
    Coordinates lat_lon_z;
    void openFile() override;
    static std::string parseStringTime(const std::string& time);
    static std::vector<std::string> parseBaseLine(const std::string& line, char sep);
    static std::vector<std::string> parseRoverLine(const std::string&line, char sep);
};



#endif //GEM_H
