#include "writer.ih"

void Writer::terminalSymbol(Terminal const *terminal, ostream &out)
{
    if (terminal->isSymbolic() && !terminal->isReserved())
        out <<  "    SMapVal(" << terminal->size() << ", \"" <<
                                  terminal << "\"),\n";
}
