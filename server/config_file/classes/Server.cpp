#include "Server.hpp"


Server::~Server() {}

Server::Server() : _listen(-1), _client_body_size(1000000), _server_name("Server"), _root("./www")
{}

Server::Server(const Server & s) : _listen(s._listen), _client_body_size(s._client_body_size), _server_name(s._server_name), _root(s._root)
{}


Server &Server::operator=(const Server & s)
{
    _listen = s._listen;
    _root = s._root;
    _client_body_size = s._client_body_size;
    _server_name = s._server_name;
}


