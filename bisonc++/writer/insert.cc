#include "writer.ih"

void Writer::insert(Terminal::ConstVector const &tokens) const
{
    *d_out << "\n"
            "    // Symbolic tokens:\n"
            "    enum Tokens__\n"
            "    {\n";

    for_each(tokens.begin(), tokens.end(),
        FnWrap::unary(insertToken, 0, *d_out));

    *d_out <<  "    };\n"
           "\n";
}
