
#include <exceptions.h>
#include <string>

using namespace std::string_literals;

error::error(const std::string &arg) : runtime_error("Error : "s + arg) {}

error_interval::error_interval() : error("Wrong time interval") {}

error_scale::error_scale(const int id) : error("Note scale out of bounds:"s + std::to_string(id)) {}