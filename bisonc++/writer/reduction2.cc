#include "writer.ih"

void Writer::reduction(Element const *symb, ReductionContext &context)
{
    Symbol const *symbol = dynamic_cast<Symbol const *>(symb);

    context.out << 
        "    { "                                    
             "{" << OM::sr << symbol << "}, "       // reduce on this symbol
                                                    // reduce by this rule nr
             "{" << setw(4) << -static_cast<int>(context.ruleNr) << "} "
        "}, // " << symbol << "\n";                 // show the N's name
}
