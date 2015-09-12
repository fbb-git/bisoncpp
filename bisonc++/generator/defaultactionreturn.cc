#include "generator.ih"

void Generator::defaultActionReturn(ostream &out) const
{
    if (d_arg.option('N'))
        return;

    key(out);

    out << 
        "                            // save default non-nested block $$\n"
        "    if (int size = s_productionInfo[production].d_size)\n"
        "        d_val__ = d_vsp__[1 - size];\n";
}
