#include "options.ih"

void Options::setAccessorVariables()
{
    setBooleans();
    setBasicStrings();
    setPathStrings();
    setQuotedStrings();
    setSkeletons();

    if (d_arg.option(0, "no-default-constructors"))
        d_constructorChecks.triVal = OFF;

    if (d_arg.option(0, "warn-tag-mismatches"))
        d_warnTagMismatches.triVal = ON;
}




