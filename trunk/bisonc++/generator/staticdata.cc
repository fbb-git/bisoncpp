#include "generator.ih"

void Generator::staticData(ostream &out) const
{
    d_writer.useStream(out);

    key(out);

    d_writer.productions();
    d_writer.srTables();
    d_writer.statesArray();

    if (d_debug)
        d_writer.symbolicNames();


    out << "} // anonymous namespace ends\n"
            "\n";

    if (d_debug)
        out << "\n"
            "std::ostringstream " << d_baseclassScope << "s_out__;\n"
            "\n";
}





