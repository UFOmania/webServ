#include "Server.hpp"

bool isNumber(std::string & s);

Server::~Server() {}

Server::Server() : _listen(-1), _client_body_size(1000000), _server_name("Server")
{}



Server::Server(const Server & s) // not complet
{}


Server &Server::operator=(const Server & s) // not complet
{
    _listen = s._listen;
    _root = s._root;
    _client_body_size = s._client_body_size;
    _server_name = s._server_name;
}

void Server::SetServerName(const std::string & val)             {   _server_name = val;                         }
void Server::SetRoot(const std::string & val)                   {    _root = val;                               }
void Server::SetIndex(const std::string & val)                  {   _index = val;                               }
void Server::SetClientBodySize(const size_t & val)              {   _root = val;                                }
void Server::SetListen(const int & val)                         {   _listen = val;                              }
void Server::AddErrorPage(const errorPages_t & val)             {   _error_pages.push_back(val);                }
void Server::AddLocation(const Location & location)             {   _locations.push_back(Location(location));   }

Location *Server::EditLocation(int idx)
{
    int locations_count =  _locations.size(); 
    if (locations_count > 0 && idx >= 0 && idx < locations_count)
        return &(_locations[idx]);
    return NULL;

}

const std::string &Server::GetRoot() const {return _root;}
const std::string &Server::GetIndex() const {return _index;}

