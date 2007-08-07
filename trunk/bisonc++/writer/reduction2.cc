#include "writer.ih"

void Writer::reduction(Element const *symb, ReductionContext &context)
{
    Symbol const *symbol = dynamic_cast<Symbol const *>(symb);
    ostringstream out;

    out << OM::sr << symbol;
    context.table << out.str() << -static_cast<int>(context.ruleNr);

    out.str("");
    out << "// " << symbol;
    context.table << out.str();
}
