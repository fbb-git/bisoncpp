#include "writer.ih"

void Writer::insert(Terminal const *token, TokenContext &context)
{
    context.out <<  "        " << token;

    if (token->value() != ++context.lastValue)
    {
        context.lastValue = token->value();
        context.out << " = " << context.lastValue;
    }
    context.out << ",\n";
}
