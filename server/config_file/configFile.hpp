#ifndef CONFIGFILE_HPP
#define CONFIGFILE_HPP

#include <iostream>
#include <ctype.h>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>
#include "config_file/classes/Server.hpp"
#include "server/config_file/classes/ConfigFileTypes.hpp"


#include "ConfigException.hpp"

#define RESET   "\033[0m"
#define BOLD    "\033[1m"

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

void normalizeConfigFormat(std::string &conf);
bool configSyntaxValidator(std::string & conf);
bool validateShape(Configtokens &t);
void tokenizeConfig(std::string & conf, Configtokens & tokens);
bool validateBlocks( std::string & conf);
void putErr(std::string msg);
bool isWord(std::string & s);
void parse(Configtokens & tokens);
void validateServer(serverToken_t &server, Server & s);


#endif