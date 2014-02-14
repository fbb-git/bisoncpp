#include "generator.ih"

bool Generator::errExisting(string const &fileName, string const &option,
                             string const &pattern) const
{
    if (not d_options.specified(option))
        return false;

    if (not grep(fileName, pattern))
    {
        emsg << '`' << fileName << 
            "' exists, option/directive `" << option << "' ignored" << endl;
        return true;
    }
    
    return false;
}
