#include "writer.ih"

void Writer::insert(Terminal::ConstVector const &tokens) const
{
    *d_out << "\n"
            "    // Symbolic tokens:\n"
            "    enum Tokens__\n"
            "    {\n";

    size_t lastTokenValue = 0;

    for_each(tokens.begin(), tokens.end(),
        FnWrap::unary(insertToken, lastTokenValue, *d_out));

    *d_out <<  "    };\n"
           "\n";
}
