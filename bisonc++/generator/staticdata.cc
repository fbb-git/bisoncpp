#include "generator.ih"

void Generator::staticData(ostream &out) const
{
    key(out);

    productionInfo(out);
    srTables(out);
    stateArray(out);

    if (d_debug)
    {
        symbolData(out);
        out << 
            "std::ostringstream " << d_baseclassScope << "s_out;\n"
            "\n";
    }
}





