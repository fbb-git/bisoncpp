#ifndef _INCLUDED_GRAMMAR_
#define _INCLUDED_GRAMMAR_

#include <vector>
#include <set>
#include <algorithm>

#include "../state/state.h"
#include "../stateinfo/stateinfo.h"

class Grammar
{
    enum Action
    {
        ACCEPT,
        SHIFT,
        REDUCE,
        RETRY,
        NO_TRANSITIONS
    };

    std::vector<StateInfo> d_stateInfo;
    std::vector<unsigned> d_stack;
    Symbol const *d_token;
    unsigned d_state;

    public:
        void deriveSentence();

    private:
        static void insert(State const *state, Grammar &grammar)
        {
            grammar.d_stateInfo.push_back(StateInfo(state));
        }

        Action action(StateInfo &state);
        
        void prepareDerivation();
        void reduce(StateInfo &state);
        bool derive();
};

        
#endif
