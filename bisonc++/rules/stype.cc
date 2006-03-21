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

//    string const &curName = name();

//    if (static_cast<int>(idx) < 0)
//        msg() << "In " << curName << ": element " << static_cast<int>(idx) <<
//                "refers to a rule using " << curName << 
//                "  as element" << warning;
//    else if (idx > size)
//        msg() << "In " << curName << ": referral to element " << idx << 
//                " in a  production having " << size << 
//                 " elements" << err;
//    else if (!idx)
//        msg() << "Element $0 not defined. Maybe use $-1 instead?" << err;

//    if (static_cast<int>(idx) > static_cast<int>(size))
//        msg() << "In " << curName << ": referral to element " << idx << 
//                " in a  production having " << size << 
//                 " elements" << err;

//    return ret;
}


