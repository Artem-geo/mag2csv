#ifndef TXT_READER_H
#define TXT_READER_H

#include "Magnetometer.h"

class Utils {
public:
    static MagInputParams parseCommandInputFile(int argc, char* argv[]);
    static MagMake parseMagMake(const std::string& mag_make);
    static MagType parseMagType(const std::string& mag_type);
    static Date parseDateFormat(const std::string& input_date);
    static char parseSeparator(const std::string& input_separator);
};

#endif //TXT_READER_H
