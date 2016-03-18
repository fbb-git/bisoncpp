#include "options.ih"

// static

Options::Value Options::valueOf(string const &key, Value byDefault,
                                                    unsigned mask)
{
    auto entry = s_value.find(String::lc(key));

    if (entry == s_value.end())
        return byDefault;

    Value ret = entry->second;

    return ret & mask ? ret : byDefault;
}
