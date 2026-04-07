#include "configFile.hpp"

void putErr(std::string msg)
{
	std::cerr << RED << "Error:" << msg << RESET << std::endl;
}

bool isSpecialToken(std::string & token)
{
    return token == "}" || token == "{" || token == ";";
}

bool isWord(std::string & s)
{
	return s != "{" && s != "}" && s != ";"; 
}