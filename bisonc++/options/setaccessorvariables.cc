#include "options.ih"

void Options::setAccessorVariables()
{
    setBooleans();
    setBasicStrings();
    setPathStrings();
    setQuotedStrings();
    setSkeletons();

    if (specified("scanner-class-name") and not specified("scanner"))
        wmsg << "option/directive `scanner-class-name' ignored:\n"
                "          requires option/directive `scanner'" << endl;
}




