#include "state.ih"

//        struct StatusOrReduce
//        {
//            Reductions &reductions;
//            ShiftReduce::Status status;
//        };

void State::writeStateArray(State const *sp, WSAContext &context)
{
    State const &state = *sp;

    Reductions reductions;
                            // when a state uses shifts/accept, then its last
                            // index value is stored as a positive value. This
                            // is used by the parser to see whether another
                            // token should be retrieved from the lexical
                            // scanner.
    StatusOrReduce sor = {reductions, ShiftReduce::REDUCE};

    msg() << "\n"
            "Inspecting reductions of state " << state.d_idx << info;

        // visit the elements in the action table d_action: register if the
        // state is the ACCEPT state and/or uses shifts. All reductions are
        // handled by the Reductions object, receiving a pointer to a token
        // and a pointer to a production

     for_each(state.d_action.begin(), state.d_action.end(),
             Wrap1c<ActionTable::value_type, StatusOrReduce>
                   (&setStatusOrReduce, sor));
 
     reductions.setDefault();
    
            // Write the table header
    context.out << "\n" 
            "SR s_" << state.d_idx << "[] =\n"
            "{\n" <<
            "    {"
                    "{" << 
                        s_stateName[state.d_type] << 
                    "}, "
                    "{" <<
                    (
                        sor.status & 
                        (ShiftReduce::ACCEPT | ShiftReduce::SHIFT) ? 
                            "" 
                        : 
                            "-"
                    ) <<   
                    (
                        state.d_action.size() - reductions.count() + 
                        reductions.used() + state.d_goto.size() + 1
                    ) <<
                    "}"
                "}, // " <<
                        state.d_action.size()   << ", " <<  // temporarily
                        reductions.used()       << " (" << 
                        reductions.count()      << "), " << 
                        state.d_goto.size()     << " "  <<
                (
                        sor.status & ShiftReduce::ACCEPT ?
                            "ACCEPTS" 
                    :
                        sor.status & ShiftReduce::SHIFT ?
                            "SHIFTS"
                    :
                            "REDUCES"
                ) << "\n";

       // write the accept and shift transitions
    for_each(state.d_action.begin(), state.d_action.end(),
            Wrap1c<ActionTable::value_type, WSAContext>
                  (&writeAcceptAndShiftTransition, context));

        // write the goto transitions
    for_each(state.d_goto.begin(), state.d_goto.end(), 
        Wrap1c<GoToTable::value_type, ostream>
              (&writeGoToTransition, context.out));

     if (!reductions.hasDefaultReduction())
         context.out << "    {{0}, {0}}\n";
     else
         context.out << 
             "    {"
                     "{0}, "
                     "{" << 
                        -reductions.defaultReduction() <<
                     "}"
                  "} // DEFAULT_REDUCTION\n";

    context.out << "};\n";
}




