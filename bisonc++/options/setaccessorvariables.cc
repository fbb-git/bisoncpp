#include "options.ih"

void Options::setAccessorVariables()
{
    setBooleans();

                    // true if --target-directory was specified
    bool targetDirOption = setBasicStrings();

    setPathStrings(targetDirOption);

    setQuotedStrings();
    setSkeletons();
}




