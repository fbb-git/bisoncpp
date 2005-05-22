#include "rules.ih"

namespace {
    string const ret;
}

string const &Rules::sType(unsigned idx) const
{
    unsigned size = d_currentProduction->size();
    
    if (idx && idx <= size)
        return (*d_currentProduction)[idx - 1].sType(); 

    if (idx > size)
        msg() << "In this context the production has " << size << 
                 " elements, not (yet) " << idx << err;
    else if (!idx)
        msg() << "Element $0 not defined" << err;

    return ret;
}


