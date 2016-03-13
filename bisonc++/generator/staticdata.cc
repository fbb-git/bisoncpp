#include "generator.ih"

void Generator::staticData(ostream &out) const
{
    d_writer.useStream(out);

    key(out);

    d_writer.productions();
    d_writer.srTables();
    d_writer.statesArray();

    if (d_debug || d_printTokens)
        d_writer.symbolicNames();

    if (d_warnTagMismatches)
    {
        out << "    char const *aTag__Name__[] = {\n";
        for (auto const &poly: d_polymorphic)
            out << "        \" << poly.first << "\",\n";
        out <<     "        \"<default>\"\n"
               "    };\n";
    }

    out << "} // anonymous namespace ends\n"
            "\n";
}
