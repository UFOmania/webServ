#ifndef CONFIGFILE_HPP
#define CONFIGFILE_HPP

#include <iostream>
#include <ctype.h>
#include <sstream>
#include <vector>
#include <iterator>

#define RESET   "\033[0m"
#define BOLD    "\033[1m"

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

struct errorPages_s
{
    std::string errorCode;
    std::string pagePath;
};

struct cgiPass_s {
    std::string extension;
    std::string path;
};
struct redirection_s {
    std::string new_path;
    std::string status;
};



struct location_s
{
    std::string path;
    std::string index;
    std::string root;
    std::string upload_path;
    std::string auto_index;
    struct redirection_s redirection;
    std::vector <std::string> allow_methods;

    bool allowGET;
    bool allowPOST;
    bool allowDELETE;
    std::string client_body_size;
    std::vector < struct cgiPass_s > cgi_pass;
};

struct token_s {
    std::string listen;
    std::string sever_name;
    std::string root;
    std::string index;
    std::string client_body_size;
    std::vector < struct errorPages_s > error_pages;
    std::vector < struct location_s > locations;
};

#define Configtokens std::vector<std::string>

void normalizeConfigFormat(std::string &conf);
bool configSyntaxValidator(std::string & conf);
bool validateShape(Configtokens &t);
void tokenizeConfig(std::string & conf, Configtokens & tokens);
bool validateBlocks( std::string & conf);
void putErr(std::string msg);
bool isWord(std::string & s);
void parse(Configtokens & tokens);



#endif