#include "arg.ih"

void Arg::fillLongOptions(OptStruct *optStruct,
                            std::string const &optString,
                            LongOption const * const begin,
                            LongOption const * const end)
{
    for (LongOption const *it = begin; it != end; it++, optStruct++)
        addLongOption(optStruct, optString, *it);
}
