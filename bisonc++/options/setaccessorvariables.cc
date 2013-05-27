#include "options.ih"

void Options::setAccessorVariables()
{
    setBooleans();

    setBasicStrings();

    setPathStrings();

    setQuotedStrings();
    setSkeletons();
}




