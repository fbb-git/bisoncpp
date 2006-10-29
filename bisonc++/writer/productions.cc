#include "writer.ih"

void Writer::productions() const
{
    Production::ConstVector const &prods = d_rules.productions();

    *d_out << "\n"
            "// Productions Info Records:\n" <<
            "PI s_productionInfo[] = \n"
            "{\n"
            "     {0, 0}, // not used: reduction values are negative\n";

    for_each(prods.begin(), prods.end(),
        Wrap1c<Production, ostream>(productionInfo, *d_out));

    *d_out << "};\n";
}







