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

void Location::AddCgiPass(const cgiPass_t & cgi)                    {   _cgi_pass.push_back(cgi);       }
void Location::AddRedirection(const redirection_t & red)            {   _redirections.push_back(red);   }
void Location::SetPath(const std::string & val)                     {   _path = val;                    }
void Location::SetIndex(const std::string & val)                    {   _index = val;                   }
void Location::SetRoot(const std::string & val)                     {   _root = val;                    }
void Location::SetUploadPath(const std::string & val)               {   _upload_path = val;             }
void Location::SetClientBodySize(const size_t & val)                {   _upload_path = val;             }
void Location::SetAutoindex(const bool & val)                       {   _upload_path = val;             }
void Location::SetAllowGet(const bool & val)                        {   _upload_path = val;             }
void Location::SetAllowPost(const bool & val)                       {   _upload_path = val;             }
void Location::SetAllowDelete(const bool & val)                     {   _upload_path = val;             }
const std::string &Location::GetRoot() const                        {   return _root;                   }

