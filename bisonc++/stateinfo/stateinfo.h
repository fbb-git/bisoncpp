#ifndef _INCLUDED_STATEINFO_
#define _INCLUDED_STATEINFO_

#include "../state/state.h"

class StateInfo
{
    State const *d_state;
    bool d_reducible;
    State::TransitionMapConstIterator d_begin;
    State::TransitionMapConstIterator d_end;

    public:
        StateInfo()
        {}
        StateInfo(State const *state);

        bool isAcceptState() const
        {
            return d_state->isAcceptState();
        }        
        size_t/*unsigned*/ reductionSize() const
        {
              return d_state->defaultReduction()->size();
        }
        bool hasDefaultReduction() const
        {
            return d_state->defaultReduction();
        }
        Symbol const *lhs() const
        {
            return d_state->reductionLhs();
        }
        Symbol const *nextToken();
        size_t/*unsigned*/ transit(Symbol const *token) const
        {
            return d_state->transitionMap().find(token)->second->next();
        }
        void reset()
        {
            d_begin = d_state->transitionMap().begin();            
        }
    private:
        static bool acceptTerminal(State::TransitionMapValue const &transit,
                                    State const &state);
};

        
#endif
