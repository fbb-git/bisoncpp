#include "generator.ih"

bool Generator::bolAtDebug(ostream &out, istream &in) const
{
    if (not d_debug)
        return bolAtIgnore(in);

    string line;

    while (getline(in, line))
    {
        if (line[0] == '@')
            return true;

        replaceBaseFlag(line);
        out << indent << line << '\n';
    }
    
    return false;
}
