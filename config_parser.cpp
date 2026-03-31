#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct errorPages_s
{
    int errorCode;
    std::string pagePath;
};

struct cgiPass_s {
    std::string extension;
    std::string path;
};

struct location_s
{
    std::string path;
    std::string root;
    std::string uploadPath;
    bool autoIndex;
    bool allowGET;
    bool allowPOST;
    bool allowDELETE;
    int clientBodySize;
    std::vector < struct cgiPass_s > cgiPass;
};

struct token_s {
    int listen;
    std::string sever_name;
    std::string root;
    std::string index;
    int client_body_size;
    std::vector < struct errorPages_s > errorPages;
    std::vector < struct location_s > locations;
};


void configFileError(std::string msg)
{
    std::cerr << "Config File Error :" + msg << std::endl;
}


bool ConfIsServers(std::string &str)
{
   return str.substr(0, sizeof("servers")) == "servers";
}

void build_tree(std::string &data)
{
    std::stringstream ss(data);
    std::string servers_var;
    ss >> servers_var;

    if (ConfIsServers(servers_var))
    {
        configFileError("no servers property");
        throw -1; //error 
    }
    std::string tmp;
    ss >> tmp;
    if (ss == "")


}

int main()
{
    std::ifstream in("test");
    std::string buff;
    std::string line;
    while (std::getline(in, line))
    {
        buff += line;
    }


    build_tree(buff);
    // std::cout << buff << std::endl;

}