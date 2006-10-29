#include "rules.ih"

namespace {
    string const ret;
}

string const &Rules::sType(size_t idx) const
{
    size_t size = d_currentProduction->size();
    
    return
        (idx && idx <= size) ?
            (*d_currentProduction)[idx - 1].sType()
        :
            ret;
}


