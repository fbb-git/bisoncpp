#ifndef _INCLUDED_ITEMSETS_
#define _INCLUDED_ITEMSETS_

#include <vector>
#include <set>
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

    struct StateInfo                        // see `deriveSentence()'
    {
        bool d_visited;
        std::set<Symbol const *> d_marked;
        std::set<Symbol const *> d_processed;

        StateInfo()
        :
            d_visited(false)
        {}
    };

    struct DContext1                        // see derive()
    {
        ItemSets *d_obj;
    };

    unsigned d_recheckState;
    StateVector d_state;

    std::vector<StateInfo> d_stateInfo;
    std::vector<unsigned> d_stack;

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

        void deriveSentence();

    private:
        void checkLookaheads(unsigned nextState, State const &source,
                                                 Symbol const &symbol);

        void derive(unsigned state);
        static void deriveAction(State::ActionTable::value_type const &,
                            ItemSets &object);
        void deriveInspectReduction(Production const *production);
        void deriveGoTo(StateInfo &stateInfo, unsigned state);

        bool goTo(State *dest, State const &source, Symbol const &symbol);
        void inspect(unsigned idx);             // idx in d_state[]

        bool rightOfDot(State *dest, State const &source, 
                                     Symbol const &symbol);

        static void searchState(Symbol const *value, SSContext &context);
};
#endif
