#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include "Location.hpp"

struct errorPages_s
{
    std::string errorCode;
    std::string pagePath;
};

class Server
{
    private:
        std::vector < struct errorPages_s > _error_pages;
        std::vector < class Location > _locations;

        std::string _server_name;
        std::string _root;
        size_t _client_body_size;
        int _listen;
        

    
    public:
        Server();
        ~Server();
        Server(const Server & s);
        Server &operator=( const Server & s);

        void setServerName(const std::string & val);
        void setListen(const int & val);
        void setRoot(const size_t & val);
        void setClientBodySize(const size_t & val);
        void AddErrorPage(const struct errorPage_s & val);
        void AddLocation(const Location & location)
};


#endif