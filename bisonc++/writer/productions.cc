#include "writer.ih"

void Writer::productions() const
{
    Production::ConstVector const &prods = d_rules.productions();

    *d_out << "\n"
            "// Productions Info Records:\n" <<
            "PI__ const s_productionInfo[] = \n"
            "{\n"
            "     {0, 0}, // not used: reduction values are negative\n";

    for (auto production: prods)
        productionInfo(production, *d_out);

    *d_out << "};\n";
}







