#include "writer.ih"

void Writer::insert(Terminal::ConstVector const &tokens) const
{
    *d_out << "\n"
            "    // Symbolic tokens:\n"
            "    enum Tokens__\n"
            "    {\n";

    size_t lastTokenValue = 0;

    for (auto token: tokens)
        insertToken(token, lastTokenValue, *d_out);

    *d_out <<  "    };\n"
           "\n";
}
