#include "rules.ih"

namespace {
    string const ret;
}

string const &Rules::sType(unsigned idx) const
{
    unsigned size = d_currentProduction->size();
    
    return
        (idx && idx <= size) ?
            (*d_currentProduction)[idx - 1].sType()
        :
            ret;
}


