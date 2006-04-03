#include "reductions.ih"

Reductions::iterator &Reductions::iterator::operator++()
{
    if (d_transition->isDefault() || ++d_symbol == d_transition->end())
    {
        ++d_transition;
        d_symbol = d_transition->begin();
        if (d_transition->isDefault())          // this is the default trans.
        {
            ++d_transition;                     // so skip it.
            d_symbol = d_transition->begin();
        }
    }
    return *this;
}
