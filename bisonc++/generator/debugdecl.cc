#include "generator.ih"

void Generator::debugDecl(std::ostream &out) const
{
    if (!d_debug)
        return;

    key(out);
    out << 
        "        static std::ostringstream s_out__;\n"
        "\n"
        "        std::string symbol(int value) const;\n"
        "        std::string stype__(char const *pre, STYPE__ const &semVal,\n"
        "                            char const *post = \"\") const;\n"
        "        static std::ostream &dflush(std::ostream &out);\n";
}
