#include "generator.ih"

void Generator::warnExisting(string const &fileName, string const &option,
                             string const &pattern) const
{
    if (not d_options.specified(option))
        return;

    if (not grep(fileName, pattern))
        wmsg << '`' << fileName << 
            "' exists, option/directive `" << option << "' ignored" << endl;
}
