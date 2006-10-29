#include "state.ih"

void State::allStates()
{
    if (!Msg::display())
        return;

    msg() << info;

    msg() << "Grammar States: " << OM::type() << info;

    if (s_insert == &State::insertExt)
        msg() << 
            "State Items show:\n"
            "   1. production number and dot-position\n"
            "   2. the item (lhs -> recognized elements . "
                                                    "elements to recognize)\n"
            "   3. the item's lookaheadset\n"
            "   4. whether (1) or not (0) it is enlarged, same for next "
                                                    "state's LA-set\n"
            "   5. ( item number(s) of its `child' items )\n"
            "   6. the next state number (-1 for reducible items)" << info;

    msg() << info;

    copy(s_state.begin(), s_state.end(), 
                ostream_iterator<State const *>(msgstream(), "\n"));

    msgstream() << info;
}
