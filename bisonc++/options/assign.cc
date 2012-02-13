#include "options.ih"

void Options::assign(std::string *target, char const *declTxt)
{
    if (target->empty())
        *target = undelimit(*d_matched);
    else
        emsg << "%" << declTxt << "multiply specified " << endl;
}
        
