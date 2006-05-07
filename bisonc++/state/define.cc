#include "state.ih"

void State::define(Production const *startProduction)
{
        // start with S' -> . S, $ ($ meaning: EOF in subsequent comment)

    s_startProduction = startProduction;
                                                // define the start-state
    State &startState = newState();

                                                // store augmented grammar
                                                // rule as kernel item
    startState.addKernelItem(Item(s_startProduction));

    startState.construct();                     // construct all states.

    s_acceptState = 
        s_state[ 
            s_state[0]->d_transition[s_startProduction->atIdx(0)]->next() 
        ];

    msg() << info;
    Indent::clear();
                                                // define the Lookaheads of
                                                // all states
    msg() << "\nDEFINING LOOK-AHEAD SETS" << info;

    startState.defineLookaheads(LookaheadSet(true));

                                                // define actions, reductions
                                                // and gotos
    State::defineActions();
}



