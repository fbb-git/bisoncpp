#include "writer.ih"

void Writer::insertToken(Terminal const *token, size_t lastValue, 
                         std::ostream &out)
{
    out <<  "        " << token;

    if (token->value() != ++lastValue)
    {
        lastValue = token->value();
        out << " = " << lastValue;
    }
    out << ",\n";
}
