#include "writer.ih"

// Writes an SR element:
//
//   { { symbol }, {nextstate} }, // comment

void Writer::transition(Next const &next, Table &table)
{
    if (Symbol const *symbol = next.symbol())
    {
        ostringstream out;

        Terminal::inserter(&Terminal::nameOrValue);
        NonTerminal::inserter(&NonTerminal::value);
        
        out << symbol;
        table << out.str() << next.next();

        out.str("");

        Terminal::inserter(&Terminal::plainName);
        NonTerminal::inserter(&NonTerminal::plainName);

        out << "// " << symbol;
        table << out.str();
    }
}







