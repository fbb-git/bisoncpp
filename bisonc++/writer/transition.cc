#include "writer.ih"

// Writes an SR element:
//
//   { { symbol }, {nextstate} },

void Writer::transition(Next const &next, ostream &out)
{
    if (Symbol const *symbol = next.symbol())
        out << "    { {" <<
            OM::sr << symbol << "}, { " <<          // shift on this symbol
            setw(3) << next.next() <<               // to this state
            "} }, // " << symbol << "\n";           // show the symbol
}







