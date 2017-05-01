#include "state.ih"

    // insert this State's _error_ LA set into the generated parse.cc file
    // at this point it has already been determined that this state is an
    // ERROR state.
void State::insertLAset(ostream &out) const
{
    out << "    {";

    bool hasEOF = false;

    for (StateItem const &item: d_itemVector)
    {
        Symbol const *symbol = item.symbolAtDot();

        if (symbol != 0 and symbol->value() == 0) // item at dot is _error_
            hasEOF |= item.lookaheadSet().basicLAset(out);
    }

    if (hasEOF)
        out << "_EOF_";

    out << "},";
}
