#include "state.ih"

    // insert this State's _error_ LA set into the generated parse.cc file
    // at this point it has already been determined that this state is an
    // ERROR state.
void State::insertLAset(ostream &out) const
{
    out << "    {";

    bool hasEOF = false;

    ostringstream ostr;
    for (StateItem const &item: d_itemVector)
    {
        Symbol const *symbol = item.symbolAtDot();

        if (symbol != 0 and symbol->value() == 0) // item at dot is _error_
            hasEOF |= item.lookaheadSet().basicLAset(ostr);
    }

    if (hasEOF)
        out << ostr.str() << "_EOF_";
    else
    {
        out << ostr.str().substr(0, ostr.str().length() - 2);
    }

    out << "},";
}


