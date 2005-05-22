#include "arg.ih"

/*
    called by fillLongOption() to create the array of `struct option'
    (OptStruct) elements to be interpreted by getopt_long()
*/
void Arg::addLongOption(OptStruct *optStruct,
                            string const &optString,
                            LongOption const &longOption)
{
    static int notUsed;

    optStruct->name = longOption.d_name.c_str();

    if (longOption.d_optionChar)       // existing option
    {
        optStruct->has_arg = setOptionType(optString, longOption);
        optStruct->flag    = 0;
        optStruct->val     = longOption.d_optionChar;
    }
    else
    {
        optStruct->has_arg = longOption.d_type,
        optStruct->flag    = &notUsed;
    }
}
