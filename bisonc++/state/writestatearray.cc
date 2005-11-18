#include "state.ih"

void State::writeStateArray(State const *sp, WSAContext &context)
{
    State const &state = *sp;

    unsigned nDefaults = 0;
    bool usesShift = false; // when a state uses a shift, then its last index
                            // value is stored as a positive value. This is
                            // used by the parser to see whether another token
                            // should be retrieved from the lexical scanner.

    Production const *defaultReduction = 0;

    for 
    (
        ActionTableConstIter actionIter = state.d_action.begin();
            actionIter != state.d_action.end();
                ++actionIter
    )
    {
        ShiftReduce const &sr = actionIter->second;

        if (sr.shift())
            usesShift = true;
        else if (!sr.accept())
        {
            if (!defaultReduction)
                defaultReduction = actionIter->second.production();

            nDefaults += 
                defaultReduction == actionIter->second.production();
        }
    }
    
    context.out << "\n" 
            "SR s_" << state.d_idx << "[] =\n"
            "{\n" <<
            "    {"
                    "{" << 
                        s_stateName[state.d_type] << 
                    "}, "
                    "{" <<
                        (usesShift ? "" : "-") <<   
                        (state.d_action.size() + state.d_goto.size() - 
                                                            nDefaults + 1) << 
                    "}"
                "}," << 
                        (usesShift ? " // SHIFTS" : "") << "\n";

    for 
    (
        ActionTableConstIter actionIter = state.d_action.begin();
            actionIter != state.d_action.end();
                ++actionIter
    )
    {
        ShiftReduce const &sr = actionIter->second;

        if (defaultReduction && sr.production() == defaultReduction)
            continue;

        Symbol const *symbol = actionIter->first;

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
            context.out << 
                static_cast<int>
                (
                    sr.shift() ? 
                        sr.state() 
                    : 
                        -sr.production()->nr()
                );
        context.out << 
                "}"
            "},\n";
    }

    for 
    (
        GoToTableConstIter gotoIter = state.d_goto.begin();
            gotoIter != state.d_goto.end();
                ++gotoIter
    )
        context.out << 
            "    {"
                    "{" << 
                        gotoIter->first->nr() << 
                    "}, "
                    "{" <<
                            gotoIter->second << 
                    "}"
                "}, // " << 
                            gotoIter->first->name() << "\n";


    if (defaultReduction)
        context.out << 
            "    {"
                    "{"
                        "0"
                    "}, "
                    "{" << 
                        static_cast<int>(-defaultReduction->nr()) << 
                    "}"
                 "} // DEFAULT_REDUCTION\n";
    else
        context.out << "    {{0}, {0}}\n";

    context.out << "};\n";

    state.d_defaultReduction = defaultReduction;
}




