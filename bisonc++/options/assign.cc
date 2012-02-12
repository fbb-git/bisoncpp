#include "options.ih"

void Options::assign(std::string *target, char const *declTxt)
{
    if (target->empty())
        *target = undelimit();
    else
        emsg << "%" << declTxt << "multiply specified " << endl;
}
        
