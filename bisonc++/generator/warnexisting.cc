#include "generator.ih"

void Generator::warnExisting(string const &fileName, string const &option,
                             string const &expectedOptionValue,
                            string const &pattern) const
{
    if (not grep(fileName, pattern))
        wmsg << '`' << fileName << 
            "' exists, option/directive `" << option << ' ' <<
            expectedOptionValue << "' ignored" << 
//            "\npattern = `" << pattern << '\'' <<
            endl;
}
