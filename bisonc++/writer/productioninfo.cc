#include "writer.ih"

void Writer::productionInfo(Production const *production, ostream &out) 
{
    NonTerminal const *np = NonTerminal::downcast(production->lhs());
    out << "     {" << np->value() << ", " << 
        production->size() << "}, // " << production << '\n';
}







