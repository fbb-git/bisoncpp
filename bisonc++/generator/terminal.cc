#include "generator.ih"

void Generator::terminal(Terminal const *terminal, TContext &context)
{
    if (terminal->isSymbolic())
        context.out <<  "    SMapVal(" << terminal->value() << ", \"" <<
                                          terminal << "\"),\n";
}
