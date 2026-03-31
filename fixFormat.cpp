#include <iostream>
#include <ctype.h>

bool isDoubleSpace(std::string &conf, std::string &newConf, int idx)
{
    return (std::isspace(conf[idx]) && (std::isspace(*(newConf.end() - 1)) || newConf.empty()));
}

std::string removeDoubleSpaces(std::string &conf)
{
    std::string newConf;
    size_t i = 0;
    bool space = false;

    while (i < conf.length())
    {
        if (isDoubleSpace(conf, newConf, i))
        {
            i++;
            continue;
        }
        else
        {
            newConf += conf[i];
            i++;
        }
    }
    if (std::isspace(*(newConf.end() - 1)))
        newConf.pop_back();
    return newConf;
}

bool isSpecialCharacter(int c)
{
    return c == '{' || c == '}' || c == ';';
}

std::string fixSpecialCharactersPadding(std::string &conf)
{
    std::string newConf;
    for (int i = 0; i < conf.length(); i++)
    {
        if (isSpecialCharacter(conf[i]))
        {
            if (i != 0 && !std::isspace(*(newConf.end())))
                newConf += ' ';

            newConf += conf[i];

            if (conf[i + 1] && !std::isspace(conf[i + 1]))
                newConf += ' ';
        }
        else
            newConf += conf[i];
    }
    return newConf;
}

void turnAllWhiteSpacesToSpace(std::string &conf)
{
    for(int i = 0; i != conf.length(); i++)
    {
        if (std::isspace(conf[i]))
            conf[i] = ' ';
    }
}

void fixConfigFormat(std::string &conf)
{

    std::string newConf = removeDoubleSpaces(conf);
    newConf = fixSpecialCharactersPadding(newConf);
    turnAllWhiteSpacesToSpace(newConf);


    // std::cout << "|" << newConf << "|" << std::endl;
    conf = newConf;
}

int main()
{

    std::string ss(" };");
    fixConfigFormat(ss);
    std::cout << "->" << ss << "<-" << std::endl;
    
}