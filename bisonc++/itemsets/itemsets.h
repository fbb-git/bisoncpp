#ifndef _INCLUDED_ITEMSETS_
#define _INCLUDED_ITEMSETS_

#include <vector>
#include <algorithm>

#include "../state/state.h"

class ItemSets
{
    typedef std::vector<State *>
            StateVector;
    typedef std::vector<State const *>
            StateConstVector;
    enum 
    {
        COMPLETED = UINT_MAX
    };

    struct SSContext                        // searchStateContext
    {
        State &state;
        ItemSets &obj;
    };

    unsigned d_recheckState;
    StateVector d_state;

    public:
        ItemSets();
                                                    // define the itemsets.
        void define(Production const *startProduction);

        unsigned nStates() const
        {
            return d_state.size();
        }
        void showConflicts()
        {
            for_each(d_state.begin(), d_state.end(), 
                     &State::showStateConflicts);
        }
        void showParsingTables() const;
        StateConstVector const &states() const
        {
            return *reinterpret_cast<StateConstVector const *>(&d_state);
        }
    private:
        void checkLookaheads(unsigned nextState, State const &source,
                                                 Symbol const &symbol);

        bool goTo(State *dest, State const &source, Symbol const &symbol);
        void inspect(unsigned idx);             // idx in d_state[]

        bool rightOfDot(State *dest, State const &source, 
                                     Symbol const &symbol);

        static void searchState(Symbol const *value, SSContext &context);
};
#endif
