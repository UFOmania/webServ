
#include <ConfigException.hpp>

ConfigException::ConfigException(){}
ConfigException::~ConfigException(){}
ConfigException::ConfigException(std::string msg) : _msg(msg) {}

const char * ConfigException::what() const
{
    return std::string("Error: " + _msg).c_str();
}
