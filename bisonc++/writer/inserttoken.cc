#include "writer.ih"

void Writer::insertToken(Terminal const *token, size_t &lastTokenValue, 
                         std::ostream &out)
{
    out <<  "        " << token;

    if (token->value() != ++lastTokenValue)
    {
        lastTokenValue = token->value();
        out << " = " << lastTokenValue;
    }
    out << ",\n";
}
