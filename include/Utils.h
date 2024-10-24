#ifndef TXT_READER_H
#define TXT_READER_H

#include "Magnetometer.h"

class Utils {
public:
    static Mag_input_params parse_command_input_file(int argc, char* argv[]);
    static Mag_make parse_mag_make(const std::string& mag_make);
    static Mag_type parse_mag_type(const std::string& mag_type);
    static Date parse_date_format(const std::string& input_date);
    static char parse_separator(const std::string& input_separator);
};

#endif //TXT_READER_H
