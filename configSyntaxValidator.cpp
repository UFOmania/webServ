#include "configFile.hpp"

bool validateBlocks( std::string & conf)
{
    int p = 0;
    for(size_t i = 0; i < conf.length() ; ++i)
    {
        switch (conf[i])
        {
            case ('{'): p++; break;
            case ('}'): p--; break;
        }
        if (p < 0) return false;
    }
    return (p == 0);
}

void tokenizeConfig(std::string & conf, std::vector<std::string> &tokens)
{
    std::stringstream ss(conf);
    std::string str;

    while (ss >> str)
    {
        tokens.push_back(str);
    }
}

int isValidServerField(std::vector<std::string>::iterator & tokenPtr)
{
    char *allowed_keys[] = {
        "listen",
        "server_name",
        "root",
        "index",
        "client_body_size"};
    
    char *allowd_groups[] = {
        "error_page",
        "locations"
        };

    for(int i = 0; i < sizeof (allowed_keys); i++)
    {
        if (*tokenPtr == allowed_keys[i])
        {
            tokenPtr++;
            return 1;
        }
    }
    for(int i = 0; i < sizeof (allowd_groups); i++)
    {
        if (*tokenPtr == allowd_groups[i])
        {
            tokenPtr++;
            return 2;
        }
    }
    return 0;
}
bool isValidLocationField(std::string &token)
{
    char *allowed_fields[] = {
        "root",
        "index",
        "client_body_size",
        "allow_methods",
        "auto_index",
        "upload_path",
        "return",
        "cgi_pass"
        };

    for(int i = 0; i < sizeof (allowed_fields); i++)
    {
        if (token == allowed_fields[i])
            return true;
    }
    return false;
}

int identifyTokenType(std::vector<std::string>::iterator & tokenPtr)
{
    int type;

    if (*tokenPtr == "error_page")
        type = ERROR_PAGE;
    else if (*tokenPtr == "location")
        type = LOCATION;
    else if (*tokenPtr == "}" || *tokenPtr == "{" || *tokenPtr == ";")
        type = SPECIAL_CHAR;
    else
        type = KEY;
    
    tokenPtr++;
    return type;
}

bool isSpecialToken(std::string & token)
{
    return token == "}" || token == "{" || token == ";";
}

bool jumpCurlyBrackets(std::vector<std::string>::iterator &tokenPtr, int &curlyBracketsDepth)
{
    if (*tokenPtr == "{")
    {
        tokenPtr++;
        curlyBracketsDepth++;
        return true;
    }
    else if (*tokenPtr == "}")
    {
        tokenPtr++;
        curlyBracketsDepth--;
        return true;
    }

    return false;
}

void validateKeyValue(std::vector<std::string>::iterator &tokenPtr)
{
    if ()
}
void validateErrorPage(std::vector<std::string>::iterator &tokenPtr)
{

}
void validateLocation(std::vector<std::string>::iterator &tokenPtr)
{

}

bool validateServerPart(std::vector<std::string>::iterator &tokenPtr)
{
    if (*tokenPtr != "{")
        return false; // no curlyBrackets after server token 

    int curlyBracketsDepth = 1;

    while (curlyBracketsDepth)
    {
        if (jumpCurlyBrackets(tokenPtr, curlyBracketsDepth))
            continue;

        if (curlyBracketsDepth == 0)
            break;
        
        if (isValidServerField(tokenPtr) == false)
            return false; //unknown field
        
        tokenPtr++;
        int id = identifyTokenType(tokenPtr);
        switch (id)
        {
            case KEY:
                validateKeyValue(tokenPtr);
                break;
            case ERROR_PAGE:
                validateErrorPage(tokenPtr);
                break;
            case LOCATION:
                validateLocation(tokenPtr);
                break;
            default:
                return false ;//error
                break;
            
        }
        
        // tokenPtr++;
        // if (*tokenPtr != ";")
        //     return false; //field must have one value

            
    }
}

bool validateSyntax(std::vector<std::string> &tokens)
{
    for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++)
    {
        if (*it == "server")
        {
            validateServerPart(it, tokens.end());
        }
    }
}

bool configSyntaxValidator(std::string & conf)
{
    if (validateBlocks(conf) == false)
    {
        return false;
    }
    std::vector<std::string> tokens;
    tokenizeConfig(conf, tokens);

    // while (!tokens.empty())
    // {
    //     std::cout << tokens.front().data << " \n"; 
    //     tokens.pop_front();
    // }

    validateSyntax(tokens);

    return true;
}
