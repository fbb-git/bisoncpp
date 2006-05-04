#include "grammar.ih"

// This function is part of the set of functions which determine whether a
// grammar derives any sentences. See derivesentence.cc

// Called by derivesentence.cc

bool Grammar::derive() 
{
    d_token = 0;
    d_stack.push_back(0);

    while (true)
    {
        d_state = d_stack.back();
        StateInfo &state = d_stateInfo[d_state];   

        switch (action(state))
        {
            case ACCEPT:
            return true;

            case SHIFT:
                d_stack.push_back(d_state);
                d_stateInfo[d_state].reset();                
                d_token = 0;
            break;

            case REDUCE:
                reduce(state);
            break;

            case RETRY:
                d_token = 0;
            break;

            case NO_TRANSITIONS:
                if (d_stack.size() == 1)
                    return false;

                d_stack.pop_back();
                d_state = d_stack.back();
                d_token = 0;
            break;
        }    
    }       
}



