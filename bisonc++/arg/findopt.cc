#include "arg.ih"

unsigned Arg::findopt(int optchar) const
{
    vector<IntStringPair>::const_iterator
        it = find_if(d_optv.begin(), d_optv.end(), 
                        FirstCompare<char>(optchar));

    return it - d_optv.begin();
}
