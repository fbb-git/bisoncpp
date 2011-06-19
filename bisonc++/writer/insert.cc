#include "writer.ih"

void Writer::insert(Terminal::ConstVector const &tokens) const
{
    *d_out << "\n"
            "    // Symbolic tokens:\n"
            "    enum Tokens__\n"
            "    {\n";

    size_t lastTokenValue = 0;

    for_each(
        tokens.begin(), tokens.end(),
        [&, d_out](Terminal const *token)
        {
            insertToken(token, lastTokenValue, *d_out);
        }
    );

    *d_out <<  "    };\n"
           "\n";
}
