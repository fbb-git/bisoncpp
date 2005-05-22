#include "arg.ih"

unsigned Arg::findopt(char const *longOpt) const
{
    vector<StringStringPair>::const_iterator
        it = find_if(d_longOption.begin(), d_longOption.end(), 
                        FirstCompare<string>(longOpt));

    return it - d_longOption.begin();
}
