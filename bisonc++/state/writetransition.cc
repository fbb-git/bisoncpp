#include "state.ih"

void State::writeTransition(TransitionMapValue const &transit, 
                            WSAContext &context)
{
    if (!transit.second->hasDestination())
        return;

    Symbol const *symbol = transit.first;
 
    context.out <<  
    "    {"
           "{";
 
    if (symbol->isSymbolic() && !symbol->isReserved())
        context.out << context.baseclassScope;

    if (symbol->isTerminal()) 
        context.out << symbol->display() << "}, "
                "{" << transit.second->next() << "}"
                "},\n";
    else
        context.out << symbol->value() << "}, "
                "{" << transit.second->next() << "}"
                "}, // " << symbol->display() << "\n";
}







