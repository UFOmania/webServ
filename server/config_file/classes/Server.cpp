#include "Server.hpp"

bool isNumber(std::string & s);

Server::~Server() {}

Server::Server() : _listen(-1), _client_body_size(1000000), _server_name("Server")
{}



Server::Server(const Server & s) // not complet
{}


Server &Server::operator=(const Server & s) // not complet
{
    for(int i = 0; i < s._cgi_pass.size(); i++ )
        _cgi_pass.push_back(s._cgi_pass[i]);
    
    _listen = s._listen;
    _root = s._root;
    _client_body_size = s._client_body_size;
    _server_name = s._server_name;

    return *this;
}

void Server::SetServerName(const std::string & val)             {   _server_name = val;                         }
void Server::SetRoot(const std::string & val)                   {    _root = val;                               }
void Server::SetIndex(const std::string & val)                  {   _index = val;                               }
void Server::SetClientBodySize(const size_t & val)              {   _client_body_size = val;                                }
void Server::SetListen(const int & val)                         {   _listen = val;                              }
void Server::AddErrorPage(const errorPages_t & val)             {   _error_pages.push_back(val);                }
void Server::AddLocation(const Location & location)             {   _locations.push_back(Location(location));   }
void Server::AddCgiPass(const cgiPass_t & cgi)                  {   _cgi_pass.push_back(cgi);                   }

Location *Server::EditLocation(int idx)
{
    int locations_count =  _locations.size(); 
    if (locations_count > 0 && idx >= 0 && idx < locations_count)
        return &(_locations[idx]);
    return NULL;

}

const std::string &Server::GetRoot() const {return _root;}
const std::string &Server::GetIndex() const {return _index;}

#include <iostream>

void Server::PrintServerInfo() const
{
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "SERVER CONFIGURATION" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    // Basic Server Info
    std::cout << "\n[SERVER BASICS]" << std::endl;
    std::cout << "  Server Name:        " << _server_name << std::endl;
    std::cout << "  Listen Port:        " << _listen << std::endl;
    std::cout << "  Root Directory:     " << _root << std::endl;
    std::cout << "  Index File:         " << _index << std::endl;
    std::cout << "  Max Body Size:      " << _client_body_size << " bytes" << std::endl;

    // Error Pages
    std::cout << "\n[ERROR PAGES] (" << _error_pages.size() << ")" << std::endl;
    if (_error_pages.empty())
    {
        std::cout << "  (None configured)" << std::endl;
    }
    else
    {
        for (size_t i = 0; i < _error_pages.size(); i++)
        {
            std::cout << "  " << i + 1 << ". Error Code: " << _error_pages[i].errorCode 
                      << " -> " << _error_pages[i].pagePath << std::endl;
        }
    }

    // CGI Pass
    std::cout << "\n[CGI PASS] (" << _cgi_pass.size() << ")" << std::endl;
    if (_cgi_pass.empty())
    {
        std::cout << "  (None configured)" << std::endl;
    }
    else
    {
        for (size_t i = 0; i < _cgi_pass.size(); i++)
        {
            std::cout << "  " << i + 1 << ". Extension: ." << _cgi_pass[i].extension 
                      << " -> " << _cgi_pass[i].path << std::endl;
        }
    }

    // Locations
    std::cout << "\n[LOCATIONS] (" << _locations.size() << ")" << std::endl;
    if (_locations.empty())
    {
        std::cout << "  (None configured)" << std::endl;
    }
    else
    {
        for (size_t i = 0; i < _locations.size(); i++)
        {
            _locations[i].PrintLocationInfo(i + 1);
        }
    }

    std::cout << "\n" << std::string(60, '=') << std::endl;
}