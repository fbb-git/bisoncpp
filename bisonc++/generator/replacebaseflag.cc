#include "generator.ih"

void Generator::replaceBaseFlag(string &line) const
{
    string const &className = d_options.className();

    while (true)
    {
        size_t pos = line.rfind(s_baseFlag);

        if (pos == string::npos)
            break;

        if (line.find(s_namespaceBaseFlag) == pos)
            line.replace(pos, s_namespaceBaseFlagSize, 
                         d_options.nameSpace() + className);
        else 
            line.replace(pos, s_baseFlagSize, className);
    }
}
