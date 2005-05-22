#include "arg.ih"

int Arg::setOptionType(string const &optString,
                            Arg::LongOption const &longOption)
{
    string::size_type pos = optString.find_first_of(longOption.d_optionChar);

    if (pos == string::npos)
        throw Errno(EINVAL, "Arg::setOptionType()") <<
                insertable <<  ": short option `" << 
                static_cast<char>(longOption.d_optionChar) << 
                "' not found" << throwable;

    return optString[pos + 1] == ':' ? Arg::Required : Arg::None;
}

