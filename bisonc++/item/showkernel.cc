#include "item.ih"

void Item::showKernel(Item const &item, char const *end)
{
    msg() << item.d_production->lhs()->name() << " -> " << spool;

    for_each(item.d_production->begin(), 
             item.d_production->begin() + item.d_dot, 
             &Symbol::displaySymbol);

    msg() << " . " << spool;

    for_each(item.d_production->begin() + item.d_dot, 
             item.d_production->end(), 
             &Symbol::displaySymbol);

    msg() << info;

    msg() << incindent << "(rule " << item.d_production->nr() << ", dot " <<
                item.d_dot << end << spool;
    Indent::dec();
}
