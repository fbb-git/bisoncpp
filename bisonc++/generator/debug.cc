#include "generator.ih"

void Generator::debug(ostream &out) const
{
    if (!d_debug)
        return;

    key(out);
    if (*d_line.rbegin() != '+')
        out <<  "s_out << " << d_line << " << \"\\n\" << dflush;" << endl;
    else
    {
        d_line.resize(d_line.length() - 1);
        out <<  "s_out << " << d_line << " << dflush;" << endl;
    }
}
