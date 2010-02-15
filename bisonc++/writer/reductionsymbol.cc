#include "writer.ih"

void Writer::reductionSymbol(Element const *symb, size_t ruleNr,
                             FBB::Table &table)
{
    Symbol const *symbol = dynamic_cast<Symbol const *>(symb);
    ostringstream out;

    Terminal::inserter(&Terminal::nameOrValue);
    NonTerminal::inserter(&NonTerminal::value);

    out << symbol;
    table << out.str() << -static_cast<int>(ruleNr);

    out.str("");

    Terminal::inserter(&Terminal::plainName);
    NonTerminal::inserter(&NonTerminal::plainName);

    out << "// " << symbol;
    table << out.str();
}
