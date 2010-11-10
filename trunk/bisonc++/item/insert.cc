#include "item.ih"

ostream &Item::insert(ostream &out, Production const *prod) const
{
    Terminal::inserter(&Terminal::plainName);
    NonTerminal::inserter(&NonTerminal::plainName);

    out << prod->lhs()->name() << " -> ";

    copy(prod->begin(), prod->begin() + dot(), 
             ostream_iterator<Symbol const *>(out, " "));

    out << " . ";

    copy(prod->begin() + dot(), prod->end(),
         ostream_iterator<Symbol const *>(out, " "));

    return out;
}
