#include "generator.ih"

void Generator::debugDecl(std::ostream &out) const
{
    if (!d_debug && !d_print)
        return;

    key(out);
    out << 
        "        static std::ostringstream s_out__;\n"
        "\n"
        "        std::string symbol__(int value) const;\n"
        "        std::string stype__(char const *pre, STYPE__ const &semVal,\n"
        "                            char const *post = \"\") const;\n"
        "        static std::ostream &dflush__(std::ostream &out);\n";
}
