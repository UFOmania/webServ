#include <iostream>
#include <sstream>

int main()
{
    std::string s("hello ");
    std::stringstream ss(s);
    std::string tmp;
    ss >> tmp;
    if (ss >> tmp)
        std::cout << tmp << std::endl;
        
}