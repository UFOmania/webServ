#include "configFile.hpp"


// int isValidServerField(std::vector<std::string>::iterator & tokenPtr)
// {
//     char *allowed_keys[] = {
//         "listen",
//         "server_name",
//         "root",
//         "index",
//         "client_body_size"};
    
//     char *allowd_groups[] = {
//         "error_page",
//         "locations"
//         };

//     for(int i = 0; i < sizeof (allowed_keys); i++)
//     {
//         if (*tokenPtr == allowed_keys[i])
//         {
//             tokenPtr++;
//             return 1;
//         }
//     }
//     for(int i = 0; i < sizeof (allowd_groups); i++)
//     {
//         if (*tokenPtr == allowd_groups[i])
//         {
//             tokenPtr++;
//             return 2;
//         }
//     }
//     return 0;
// }
// bool isValidLocationField(std::string &token)
// {
//     char *allowed_fields[] = {
//         "root",
//         "index",
//         "client_body_size",
//         "allow_methods",
//         "auto_index",
//         "upload_path",
//         "return",
//         "cgi_pass"
//         };
//     for(int i = 0; i < sizeof (allowed_fields); i++)
//     {
//         if (token == allowed_fields[i])
//             return true;
//     }
//     return false;
// }




// bool jumpCurlyBrackets(std::vector<std::string>::iterator &tokenPtr, int &curlyBracketsDepth)
// {
//     if (*tokenPtr == "{")
//     {
//         tokenPtr++;
//         curlyBracketsDepth++;
//         return true;
//     }
//     else if (*tokenPtr == "}")
//     {
//         tokenPtr++;
//         curlyBracketsDepth--;
//         return true;
//     }

//     return false;
// }


bool extractServers(Configtokens & t, std::vector <std::pair < int, int> > & servers)
{
    std::pair<int, int> s;
    bool server = false;
    int p = 0;

    for (size_t i = 0; i < t.size(); i++)
    {
        if (!server)
        {
            if (t[i] == "server")
            {
                server = true ;
                s.first = i;
            }
            else
                return false ;
        }
        else
        {
            if (t[i] == "{") p++;
            else if(t[i] == "}") p--;
            if (p == 0)
            {
            std::cout << "++++++\n";
                s.first += 2;
                s.second = i - 1;
                server = false;
                servers.push_back(s);
            }
        }
    }
    return true;
}

bool isServerKey(std::string & str)
{
    return (
        str == "listen" ||
        str == "server_name" ||
        str == "root" ||
        str == "index" ||
        str == "client_body_size"
    );
}
bool isServerblock(std::string & str)
{
    return (
        str == "error_page" ||
        str == "location"
    );
}

void extractSingleValue(Configtokens &t, int & idx, std::string target, std::string & dst)
{
    idx++;
    dst = t[idx];
    idx++;
    if (t[idx] != ";")
    {
        putErr(target + " have multiple Values");
        exit(1);
        // throw pls
    }
}

bool isLocation(Configtokens & t, int idx)
{
    if (t[idx] == "location")
    {
        idx++;
        if(isWord(t[idx]))
        {
            idx++;
            if (t[idx] == "{")
                return true;
            else return false;
        }
        else
            return false;
    }  
    else
        return false;

}

bool extractReturnValue(Configtokens & t, int & idx, struct redirection_s & dst)
{
    idx++;
    if (isWord(t[idx]))
    {
        dst.status = t[idx];
        idx++;
        if (isWord(t[idx]))
        {
            dst.new_path = t[idx];
            idx++;
            if (t[idx] == ";")
                return true;
            else
            {
                putErr("redirection have unknown values");
                return false;
            }

        }
        else
        {
            putErr("redirection new_path not Found");
            return false;
        }
    }
    else
    {
        putErr("redirection status not Found");
        return false;
    }
}

void extractMethodValues(Configtokens & t, int & idx, std::vector <std::string> & dst)
{
    idx++;
    while (t[idx] != ";")
    {
        dst.push_back(std::string(t[idx]));
        idx++;
    }
}

bool extractCgiValues(Configtokens & t, int & idx, std::vector <struct cgiPass_s> & dst)
{
    idx++;
    if (t[idx] == "{")
    {
        idx++;
        while (t[idx] != "}")
        {
            struct cgiPass_s c;
            c.extension = t[idx];
            idx++;
            c.path = t[idx];
            idx++;
            if (t[idx] != ";")
            {
                putErr("unknown cgi_pass value");
                return false;
            }
            else
                dst.push_back(c);
            idx++;
        }
        
    }
    else
    {
        putErr("invalid cgi_pass block");
        return false;
    }

    return true;
}

bool extractErrorPageValues(Configtokens & t, int & idx, std::vector < struct errorPages_s> & dst)
{
    idx++;
    if (t[idx] == "{")
    {
        idx++;
        while (t[idx] != "}")
        {
            struct errorPages_s e;
            e.errorCode = t[idx]; // status code
            idx++;
            e.pagePath = t[idx];// html page
            idx++;
            if (t[idx] != ";")
            {
                putErr("unknown at error_page value >"+t[idx]);
                return false;
            }
            else
                dst.push_back(e);
            idx++;
        }
        
    }
    else
    {
        putErr("invalid at error_page block");
        return false;
    }
    return true;
}
void printToken(const token_s& t);

bool checkForDoplications(Configtokens & t, std::pair<int, int> borders, std::vector <struct token_s> & dst)
{

    token_s server;
        
    for(int i = borders.first; i <= borders.second; i++)
    {
        if (isServerKey(t[i]))
        {
            if (t[i] == "listen") extractSingleValue(t, i, "listen", server.listen);
            else if (t[i] == "server_name") extractSingleValue(t, i, "server_name", server.sever_name);
            else if (t[i] == "root") extractSingleValue(t, i, "root", server.root);
            else if (t[i] == "index") extractSingleValue(t, i, "index", server.index);
            else if (t[i] == "client_body_size") extractSingleValue(t, i, "client_body_size", server.client_body_size);
            else {
                putErr("unknown Key :" + t[i]);
                return false;
            }

        }
        else if (isServerblock(t[i]))
        {
            if (isLocation(t, i))
            {
                // std::cout << BLUE << "location found : " << t[i] << RESET <<std::endl;
                // std::cout << RED << "<<<<<<"  << RESET <<std::endl;
                location_s l ;
                l.path = t[++i];
                i += 2;
                int p = 1;
                while (t[i] != "}")
                {
                    std::cout << BLUE << "      " << t[i] << RESET <<std::endl;
                    
                    //PROBLEM WITH PARENTS 
                    //
                    // if (t[i] == "}") {p--; continue;}
                    // if (t[i] == "}") {p++; continue;}


                    if (t[i] == "root") extractSingleValue(t, i, "root", l.root);
                    else if (t[i] == "index") extractSingleValue(t, i, "index", l.index);
                    else if (t[i] == "client_body_size") extractSingleValue(t, i, "client_body_size", l.client_body_size);
                    else if (t[i] == "auto_index") extractSingleValue(t, i, "auto_index", l.auto_index);
                    else if (t[i] == "upload_path") extractSingleValue(t, i, "upload_path", l.upload_path);
                    else if (t[i] == "return") extractReturnValue(t, i, l.redirection);
                    else if (t[i] == "allow_methods") extractMethodValues(t, i, l.allow_methods);
                    else if (t[i] == "cgi_pass") extractCgiValues(t, i, l.cgi_pass);

                    else {
                        putErr("unknown Key :" + t[i]);
                        return false;
                    }
                    i++;
                }
                server.locations.push_back(l);
            }
            else if (t[i] == "error_page")
            {
                extractErrorPageValues(t, i, server.error_pages);
            }
        }
        else
        {
            putErr("unexpected token " + t[i]);
            return false;
        }
        
    }
    dst.push_back(server);
    printToken(server);
    return true;
}

void printToken(const token_s& t)
{
    std::cout << BOLD << BLUE << "\n===== SERVER =====\n" << RESET;

    std::cout << CYAN << "listen: " << RESET << t.listen << "\n";
    std::cout << CYAN << "server_name: " << RESET << t.sever_name << "\n";
    std::cout << CYAN << "root: " << RESET << t.root << "\n";
    std::cout << CYAN << "index: " << RESET << t.index << "\n";
    std::cout << CYAN << "client_body_size: " << RESET << t.client_body_size << "\n";

    // 🔴 Error Pages
    std::cout << BOLD << RED << "\n-- Error Pages --\n" << RESET;
    for (size_t i = 0; i < t.error_pages.size(); i++)
    {
        std::cout << YELLOW << "[" << i << "] "
                  << "code: " << RESET << t.error_pages[i].errorCode
                  << YELLOW << " path: " << RESET << t.error_pages[i].pagePath
                  << "\n";
    }

    // 🟢 Locations
    std::cout << BOLD << GREEN << "\n-- Locations --\n" << RESET;

    for (size_t i = 0; i < t.locations.size(); i++)
    {
        const location_s& loc = t.locations[i];

        std::cout << BOLD << "\n[Location " << i << "]\n" << RESET;

        std::cout << CYAN << "path: " << RESET << loc.path << "\n";
        std::cout << CYAN << "root: " << RESET << loc.root << "\n";
        std::cout << CYAN << "index: " << RESET << loc.index << "\n";
        std::cout << CYAN << "upload_path: " << RESET << loc.upload_path << "\n";
        std::cout << CYAN << "auto_index: " << RESET << loc.auto_index << "\n";
        std::cout << CYAN << "client_body_size: " << RESET << loc.client_body_size << "\n";

        // Methods
        std::cout << YELLOW << "allowed methods: " << RESET;
        for (size_t j = 0; j < loc.allow_methods.size(); j++)
            std::cout << loc.allow_methods[j] << " ";
        std::cout << "\n";

        std::cout << YELLOW << "flags: " << RESET
                  << "GET(" << loc.allowGET << ") "
                  << "POST(" << loc.allowPOST << ") "
                  << "DELETE(" << loc.allowDELETE << ")\n";

        // 🔁 Redirection
        if (!loc.redirection.new_path.empty())
        {
            std::cout << RED << "redirection -> " << RESET
                      << loc.redirection.status << " "
                      << loc.redirection.new_path << "\n";
        }

        // ⚙️ CGI
        if (!loc.cgi_pass.empty())
        {
            std::cout << GREEN << "cgi_pass:\n" << RESET;
            for (size_t j = 0; j < loc.cgi_pass.size(); j++)
            {
                std::cout << "  " << CYAN << loc.cgi_pass[j].extension
                          << RESET << " -> "
                          << loc.cgi_pass[j].path << "\n";
            }
        }
    }

    std::cout << BLUE << "=====================\n" << RESET;
}

void parse(Configtokens & tokens)
{
    std::vector < std::pair < int,int > > servers;
    std::vector <struct token_s> ser;

    extractServers(tokens, servers); // throw pls
    std::cout << "\033[32m-- servers count : " << servers.size() << " -- \033[0m\n";
    for (int i = 0; i < servers.size(); i++)
    {

        std::cout << "\033[33m-- servers " << i << " -- \033[0m\n";
        bool status = checkForDoplications(tokens, servers[i], ser);
        if (!status)
            std::cout<< RED << "FAILED" << RESET << std::endl;
    }

    


}