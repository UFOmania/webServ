#include "isAllowed.hpp"

bool isAllowdCgi(const std::string & s)
{
    return s == ".py" || s == ".php";
}