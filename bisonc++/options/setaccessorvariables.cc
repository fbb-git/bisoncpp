#include "options.ih"

void Options::setAccessorVariables()
{
    setBooleans();
    setBasicStrings();
    setPathStrings();
    setQuotedStrings();
    setSkeletons();

    cerr << "pre-value is " << d_constructorChecks.triVal << '\n';

    if (d_arg.option(0, "no-constructor-checks"))
        d_constructorChecks.triVal = OFF;

    if (not d_polymorphic) 
    {



    if (d_arg.option(0, "warn-tag-mismatches"))
        d_warnTagMismatches.triVal = ON;
}




