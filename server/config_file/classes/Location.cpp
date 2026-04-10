#include "Location.hpp"


Location::~Location() {}

Location::Location() : 
    _allowGET(false), 
    _allowPOST(false), 
    _allowDELETE(false), 
    _autoindex(false), 
    _client_body_size(1000000)
{

}

Location::Location(const Location & l)
{
    if (&l != this)
        *this = l;
}

Location &Location::operator=(const Location & l)
{
    for(int i = 0; i < l._cgi_pass.size(); i++ )
        _cgi_pass.push_back(l._cgi_pass[i]);
        
    _path = l._path;
    _index = l._index;
    _root = l._root;
    _upload_path = l._upload_path;
    _client_body_size = l._client_body_size;
    _autoindex = l._autoindex;
    _allowDELETE = l._allowDELETE;
    _allowGET = l._allowGET;
    _allowPOST = l._allowPOST;
}


