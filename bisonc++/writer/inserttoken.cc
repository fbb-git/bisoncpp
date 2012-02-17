#include "writer.ih"

void Writer::insertToken(Terminal const *token, size_t &lastTokenValue, 
                         std::ostream &out)
{
    out <<  "        " << token;

    if (token->size() != ++lastTokenValue)
    {
        lastTokenValue = token->size();
        out << " = " << lastTokenValue;
    }
    out << ",\n";
}
