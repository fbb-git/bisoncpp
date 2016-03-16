#include "options.ih"

    // called after the grammar has been parsed (by Parser::cleanup in main)
void Options::setAccessorVariables()
{
    setBooleans();
    setBasicStrings();
    setPathStrings();
    setQuotedStrings();
    setSkeletons();

    if (d_polymorphic)
    {
        d_constructorChecks.triVal = 
                    d_arg.option(0, "no-constructor-checks") ?
                        OFF
                    :
                        ON;

        if (d_arg.option(0, "warn-tag-mismatches"))
            d_constructorChecks.triVal = ON;
    }
    else
    {
        if (d_constructorChecks.triVal == OFF)
            warnNonPolymorphic(d_constructorChecks, "no-constructor-checks");

        if (d_warnTagMismatches.triVal == ON)
            warnNonPolymorphic(d_warnTagMismatches, "warn-tag-mismatches");
    }

    Global::plainWarnings();
}




