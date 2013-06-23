#include "generator.ih"

void Generator::warnExisting(string const &fileName, string const &option) 
                                                                        const
{
    if (d_options.specified(option))
        wmsg << '`' << fileName << 
            "' exists, ignoring option/directive " << option << endl;
}
