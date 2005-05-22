#include "item.ih"

void Item::showKernel(Item const &item)
{
    msg() << "    " << item.d_production->lhs()->name() << " -> " << spool;

    for_each(item.d_production->begin(), 
             item.d_production->begin() + item.d_dot, 
             &Symbol::displaySymbol);

    msg() << " . " << spool;

    for_each(item.d_production->begin() + item.d_dot, 
             item.d_production->end(), 
             &Symbol::displaySymbol);

    msg() << "  (rule " << item.d_production->nr() << ")\n" <<
            setw(14) << " " << "Lookahead set " << item.d_lookahead << "\n" << 
            info;
}
