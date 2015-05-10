#include "item.ih"

Symbol const *Item::beyondDotIsNonTerminal() const
{
    if (d_dot < d_production->size())
    {
        Symbol const &symbol = (*d_production)[d_dot];
        if (symbol.isNonTerminal())
            return &symbol;
    }
    return 0;            
}
