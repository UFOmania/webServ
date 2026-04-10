#include "configFile.hpp"

void validateNumiricValues(token_s & server)
{
    char *end;
    int i;

    
    if (server.listen.empty())
        throw ConfigException("Invalid listen value >" + server.listen);
    i = std::strtol(server.listen.c_str(), &end, 10);
    if ((end && *end != '\0') || (i > 65535 || i < 1))
        throw ConfigException("Invalid listen value >" + server.listen);


    
    if (!server.client_body_size.empty())
    {
        i = std::strtol(server.client_body_size.c_str(), &end, 10);
        if ((end && *end != '\0') || i < 0)
        throw ConfigException("Invalid client_body_size value >" + server.listen);
    }
    
    
    for(size_t i = 0; i < server.locations.size(); i++)
    {

        i = std::strtol(server.client_body_size.c_str(), &end, 10);
        if ((end && *end != '\0') || i < 0)
            throw ConfigException("Invalid client_body_size value >" + server.locations[i].client_body_size);
    }
}

void validateboolValues(token_s & server)
{
    for(size_t i = 0; i < server.locations.size(); i++)
    {
        std::string auto_index = server.locations[i].auto_index;
        if (!auto_index.empty() && auto_index != "on" && auto_index != "off")
            throw ConfigException("Invalid auto_index value >" + auto_index);
    }
}

#include <sys/stat.h> 

bool validateFile(std::string & path, char type)
{
    struct stat info;
    if (stat(path.c_str(), &info) == 0)
    {
        if (type == 'f')
            return (S_ISREG(info.st_mode));
        else if (type == 'd')
            return (S_ISDIR(info.st_mode));
        return false;
    }
    else
        return false;
}

void validateStringValues (token_s & server)
{
    //root
    validateFile(server.root, 'd');
    validateFile(server.index, 'f');
    for(size_t i = 0; i < server.locations.size(); i++)
    {
        validateFile(server.locations[i].path, 'd');
        validateFile(server.locations[i].root, 'd');
        validateFile(server.locations[i].upload_path, 'd');
        validateFile(server.locations[i].index, 'f');
    }

}

void validateErrorPages (token_s & server)
{
    int i = 0;
    char *end;
    for(int i = 0; i < server.error_pages.size(); ++i)
    {
        errorPages_s &e = server.error_pages[i];
        if (e.errorCode.length() != 3)
            throw ConfigException("Invalid error_page Code value >" + e.errorCode);
        
        i = std::strtol(e.errorCode.c_str(), &end, 10);
        if (!end || *end != '\0' || i < 100 || i > 599)
            throw ConfigException("Invalid error_page Code value >" + e.errorCode);

        if (!validateFile(e.pagePath, 'f'))
            throw ConfigException("Invalid error_page path value >" + e.pagePath);
    }
}


void validateAllowMethods(token_s & server)
{
    for(int i = 0; i < server.locations.size(); i++)
    {
        int G,P,D = false;
        std::vector <std::string> & methods = server.locations[i].allow_methods;
        for (int j = 1; methods.size(); j++)
        {
            if (methods[j] == "GET")
            {
                if (G)
                    throw ConfigException("Dublicated Method >" + methods[j]);
                G = true;
            }
            else if (methods[j] == "POST")
            {
                if (P)
                    throw ConfigException("Dublicated Method >" + methods[j]);
                P = true;
            }
            else if (methods[j] == "DELETE")
            {
                if (D)
                    throw ConfigException("Dublicated Method >" + methods[j]);
                D = true;
            }
            else
                throw ConfigException("Invalid Method >" + methods[j]); 
        }
        
    }
}
void validateCgiPass(token_s & server)
{
    for (int i = 0; i < server.locations.size(); ++i)
    {
        for (int j = 0; j < server.locations[i].cgi_pass.size(); j++)
        {
            struct cgiPass_s & cgi = server.locations[i].cgi_pass[j];
            if (!validateFile(cgi.path, 'f'))
                throw ConfigException("Invalid cgi execution path >" + cgi.path);
        }
    }
}
void validateRedirections(token_s & server)
{
    char *end;
    int i = 0;
    for (int i = 0; i < server.locations.size(); ++i)
    {
        struct location_s & l = server.locations[i];

        if (l.redirection.status.length() != 3)
            throw ConfigException("Invalid return Code value >" + l.redirection.status);

        i = std::strtol(l.redirection.status.c_str(), &end, 10);

        if (!end || *end != '\0' || i < 300 || i > 399)
            throw ConfigException("Invalid return Code value >" + l.redirection.status);

        if (!validateFile(l.redirection.new_path, 'd'))
            throw ConfigException("Invalid return path value >" + l.redirection.status);
    }
}


void validateServer(token_s & server)
{
    validateNumiricValues(server);
    validateboolValues(server);
    validateStringValues(server);
    validateErrorPages(server);
    validateAllowMethods(server);
    validateCgiPass(server);
    validateRedirections(server);



}