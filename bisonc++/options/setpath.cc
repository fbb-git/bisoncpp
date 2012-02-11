#include "options.ih"

void Options::setPath(std::string *target, std::string const &name)
{
    if (target->empty())
        *target = undelimit(name);
}
        
