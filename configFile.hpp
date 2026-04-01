#ifndef CONFIGFILE_HPP
#define CONFIGFILE_HPP

#include <iostream>
#include <ctype.h>
#include <sstream>
#include <vector>
#include <iterator>

void normalizeConfigFormat(std::string &conf);
bool configSyntaxValidator(std::string & conf);
enum tokeType_e
{
    ERROR_PAGE, LOCATION, KEY, SPECIAL_CHAR
};
#endif