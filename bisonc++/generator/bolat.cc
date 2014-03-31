#include "generator.ih"

void Generator::bolAt(ostream &out, string &line, istream &in, bool &accept) 
                                                                        const
{
    auto iter = find(line, 0, s_atBol);

    if (iter != s_atBol.end())
        (this->*iter->function)(accept);
    else
        wmsg << "Ignoring unsupported `" << line << "' in  .in file" << endl;
}
