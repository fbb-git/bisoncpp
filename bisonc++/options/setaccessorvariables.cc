#include "options.ih"

    // called after the grammar has been parsed (by Parser::cleanup in main)
void Options::setAccessorVariables()
{
    setBooleans();
    setBasicStrings();
    setPathStrings();
    setQuotedStrings();
    setSkeletons();

    Global::plainWarnings();
}




