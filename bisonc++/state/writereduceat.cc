#include "state.ih"

void State::writeReduceAt(Element const *symbol, WRContext &context)
{
    context.out << 
        "    {"                                 // N-value
             "{" << Terminal::downcast(symbol)->value() << "}, "
             "{" << -context.nr << "}"        // reduce by this rule nr
        "}, // " << symbol->display() << "\n";    // show the N's name
}




