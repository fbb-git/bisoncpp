#include "state.ih"

void State::allStates()
{
    if (!imsg.isActive())
        return;

    imsg << "\n"
            "Grammar States: " << endl;

    if (s_insert == &State::insertExt)
        imsg << 
    "\n"
    "For each state information like the following is shown for its items:\n"
    "   0: [P1 1] S -> C  . C   { <EOF> }  0\n"
    "which should be read as follows:\n"
    "   0:          The item's index\n"
    "   [P1 1]:     The rule (production) number and current dot-position\n"
    "   S -> C . C: The item (lhs -> Recognized-symbols . "
                                                  "symbols-to-recognize)\n"
    "   { <EOF> }   The item's lookahead (LA) set\n"
    "   0           The next-element (shown below the items) describing the\n"
    "               action associated with this item (-1 for reducible "
                                                            "items)\n"
    "\n"
    "The Next tables show entries like:\n"
    "   0: On C to state 5 with (0 )\n"
    "meaning:\n"
    "   0:               The Next table's index\n"
    "   On C to state 5: When C was recognized, continue at state 5\n"
    "   with (0 )        The item(s) whose dot is shifted at the next state\n"
    "Indices (like 0:) may be annotated as follows:\n"
    "   0 (AUTO REMOVED by S/R resolution): On C ...\n"
    "       in which case a reduction using a production with unspecified\n"
    "       precedence took priority;\n"
    "or:\n"
    "   0 (removed by precedence): On C ...\n"
    "       in which case a production rule's precedence took priority\n"
    "Also, reduction item(s) may be listed\n";

    imsg << '\n';

    copy(s_state.begin(), s_state.end(), 
                ostream_iterator<State const *>(imsg, "\n"));

    imsg << endl;
}

