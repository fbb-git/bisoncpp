#include "generator.ih"

void Generator::bolAt(ostream &out, string &line, istream &in) const
{
    if (line.find("@debug") != 0)
        wmsg << "Ignoring unsupported `" << line << "' in  .in file" << endl;
    else
        bolAtDebug(out, in);
}
