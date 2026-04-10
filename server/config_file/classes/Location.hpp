#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>
#include <vector>

struct cgiPass_s {
    std::string extension;
    std::string path;
};

struct redirection_s {
    std::string new_path;
    std::string status;
};

class Location
{
    private:
        std::vector < struct cgiPass_s > _cgi_pass;
        std::string _path;
        std::string _index;
        std::string _root;
        std::string _upload_path;
        size_t      _client_body_size;
        bool        _autoindex;
        bool        _allowGET;
        bool        _allowPOST;
        bool        _allowDELETE;
        

    public:
        Location();
        ~Location();
        Location(const Location & s);
        Location &operator=( const Location & s);
};


#endif