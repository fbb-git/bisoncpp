#include "writer.ih"

// Writes an SR element:
//
//   { { symbol }, {nextstate} }, // comment

void Writer::transition(Next const &next, Table &table)
{
    if (Symbol const *symbol = next.symbol())
    {
        ostringstream out;
        
        out << OM::sr << symbol;
        table << out.str() << next.next();
        out.str("");
        out << "// " << symbol;
        table << out.str();
    }
}







