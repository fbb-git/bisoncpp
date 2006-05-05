#include "state.ih"

void State::writeStateArray(State const *sp, WSAContext &context)
{
    State const &state = *sp;
    
            // Write the table header
    context.out << "\n" 
            "SR s_" << state.d_idx << "[] =\n"
            "{\n" <<
            "    {"
                    "{" << 
                        s_stateName[state.d_type] << 
                    "}, "
                    "{" << 
                        state.d_nTransitions + state.d_reduce.size() +
                        (sp == s_acceptState) + 1 <<
                    "}"

                "}, // " <<
                (
                        sp == s_acceptState ?
                            "ACCEPTS" 
                    :
                        state.d_reduce.size() || state.d_defaultReduction ?
                            "REDUCES"
                    :
                            "SHIFTS"
                ) << "\n";

       // write the transitions
    for_each(state.d_transition.begin(), state.d_transition.end(),
        Wrap1c<TransitionMapValue, WSAContext>(writeTransition, context));

    if (sp == s_acceptState)
        context.out << "    {{" << Rules::eofTerminal()->display() << 
                                                "}, { PARSE_ACCEPT }},\n";

        // write the reductions (if any)
    for_each(state.d_reduce.begin(), state.d_reduce.end(),
        Wrap1c<ReduceMapValue, ostream>(writeReduction, context.out));

     if (!state.d_defaultReduction)
         context.out << "    {{0}, {0}}\n";
     else
         context.out << 
             "    {"
                     "{0}, "
                     "{" << 
                        -static_cast<int>(state.d_defaultReduction->nr()) <<
                     "}"
                  "} // DEFAULT_REDUCTION\n";

    context.out << "};\n";
}




