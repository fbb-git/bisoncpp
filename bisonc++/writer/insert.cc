#include "writer.ih"

void Writer::insert(Terminal::ConstVector const &tokens) const
{
    *d_out << "\n"
            "    // Symbolic tokens:\n"
            "    enum Tokens__\n"
            "    {\n";
 
    TokenContext context = {0, *d_out};

    for_each(tokens.begin(), tokens.end(),
        FnWrap1c<Terminal const *, TokenContext &>(insert, context));

    *d_out <<  "    };\n"
           "\n";
}
