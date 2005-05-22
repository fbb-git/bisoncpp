#include "generator.ih"

void Generator::debugDecl(std::ostream &out) const
{
    if (!d_debug)
        return;

    key(out);
    out << 
        "        static std::ostringstream s_out;\n"
        "\n"
        "        std::string symbol(int value) const;\n"
        "        static std::ostream &dflush(std::ostream &out);\n";
}
