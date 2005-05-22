#include "production.ih"

void Production::showElement(ostream &out, Symbol const *sp)
{
    out << " " << (sp->isReserved() ? sp->name() : sp->display());
}
