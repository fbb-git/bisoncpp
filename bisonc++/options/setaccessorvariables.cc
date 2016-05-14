#include "options.ih"

    // called after the grammar has been parsed (by Parser::cleanup in main)
void Options::setAccessorVariables()
{
    setBooleans();
    setBasicStrings();
    setPathStrings();
    setQuotedStrings();
    setSkeletons();

    string value;
    if (d_arg.option(&value, "stack-expansion"))
    {
        d_stackExpansion = stoul(value);
        if (d_stackExpansion < s_defaultStackExpansion)
            d_stackExpansion = s_defaultStackExpansion;
    }

    Global::plainWarnings();
}




