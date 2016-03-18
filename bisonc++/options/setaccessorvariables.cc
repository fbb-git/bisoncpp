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

    if (d_arg.option(&value, "constructor-checks"))
        setConstructorChecks(value, "", 0);

    if (d_arg.option(&value, 'd'))
        setDefaultAction(value, "", 0);

    if (d_arg.option(&value, "tag-mismatches"))
        setTagMismatches(value, "", 0);

    Global::plainWarnings();
}




