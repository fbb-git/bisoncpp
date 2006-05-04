#include "generator.ih"

void Generator::nonTerminal(NonTerminal const *nonTerminal, TContext &context) 
{
    context.out <<  "    SMapVal(" << nonTerminal->value() << ", \"" <<
                                        nonTerminal->name() << "\"),\n";
}
