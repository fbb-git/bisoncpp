#include "writer.ih"

void Writer::nonTerminalSymbol(NonTerminal const *nonTerminal, ostream &out)
{
    out <<  "    SMapVal(" << nonTerminal->value() << ", \"" <<
                              nonTerminal << "\"),\n";
}
