#include "rules.ih"

void Rules::updateDefaultActionLineNr(size_t lineNr) 
{
    if (d_defaultAction && d_currentProduction)
    {
        d_currentProduction->setBlockLineNr(lineNr);
        d_defaultAction = false;
    }
}
