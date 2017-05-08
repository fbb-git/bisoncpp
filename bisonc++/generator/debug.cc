#include "generator.ih"

void Generator::debug(ostream &out) const
{
    if (!d_genDebug)
        return;

    key(out);

    out << "if (d_debug__)\n" <<
        setw(d_indent + 4) << "" << flush;

    if (*d_line.rbegin() != '+')
        out <<  "s_out__ << " << d_line << " << '\\n' << dflush__;\n";
    else
    {
        d_line.resize(d_line.length() - 1);
        out <<  "s_out__ << " << d_line << ";\n";
    }
}
