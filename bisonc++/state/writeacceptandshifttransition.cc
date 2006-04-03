#include "state.ih"

// struct WSAContext                       // writeStateArrayContext
// {
//     std::string const &baseclassScope;
//     std::ostream &out;
// };


void State::writeAcceptAndShiftTransition
                (ActionTable::value_type const &action, WSAContext &context)
{
    ShiftReduce const &sr = action.second;
 
                // do not insert _default_ reductions and do not insert
                // the reduction which was found to be the default
                // reduction. 
 
    if (sr.reduce())
        return;

    Symbol const *symbol = action.first;
 
    context.out <<  
    "    {"
           "{";
 
    if (symbol->isSymbolic() && !symbol->isReserved())
        context.out << context.baseclassScope;
 
    context.out << symbol->display() << 
            "}, "
            "{";
    if (sr.accept())
        context.out << "PARSE_ACCEPT";
    else
        context.out << sr.state();
 
    context.out << 
            "}"
        "},\n";
}

