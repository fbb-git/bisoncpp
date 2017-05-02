#include "writer.ih"

// Writes an SR element:
//                            |---| <----------- if applicable
//   { { symbol }, {nextstate}, idx }, // comment

void Writer::transition(size_t errorLAidx, Next const &next, Table &table)
{
    if (Symbol const *symbol = next.symbol())
    {
        ostringstream out;

        Terminal::inserter(&Terminal::nameOrValue);
        NonTerminal::inserter(&NonTerminal::value);
        
        out << symbol;
        table << out.str() << next.next() << 
                (
                    symbol->value() == 0 ?                       // _error_
                        ", " + to_string(errorLAidx) 
                    : 
                        " "
                );

        out.str("");

        Terminal::inserter(&Terminal::plainName);
        NonTerminal::inserter(&NonTerminal::plainName);

        out << "// " << symbol;
        table << out.str();
    }
}







