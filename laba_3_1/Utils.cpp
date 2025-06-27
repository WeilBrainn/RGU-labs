#include "Utils.h"

int parseTime(const std::string& time_str) {
    size_t colon = time_str.find(':');
    int hours = std::stoi(time_str.substr(0, colon));
    int minutes = std::stoi(time_str.substr(colon + 1));
    return hours * 60 + minutes;
}