#include "writer.ih"

void Writer::insert(Terminal::ConstVector const &tokens) const
{
    *d_out << "\n"
            "    // Symbolic tokens:\n"
            "    enum Tokens\n"
            "    {\n";
 
    TokenContext context = {0, *d_out};

    for_each(tokens.begin(), tokens.end(),
        Wrap1c<Terminal, TokenContext>(insert, context));

    *d_out <<  "    };\n"
           "\n";
}
