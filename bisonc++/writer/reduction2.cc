#include "writer.ih"

void Writer::reduction(Element const *symb, ReductionContext &context)
{
    Symbol const *symbol = dynamic_cast<Symbol const *>(symb);
    ostringstream out;

    Terminal::inserter(&Terminal::nameOrValue);
    NonTerminal::inserter(&NonTerminal::value);

    out << symbol;
    context.table << out.str() << -static_cast<int>(context.ruleNr);

    out.str("");

    Terminal::inserter(&Terminal::plainName);
    NonTerminal::inserter(&NonTerminal::plainName);

    out << "// " << symbol;
    context.table << out.str();
}
