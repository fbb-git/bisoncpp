#ifndef _INCLUDED_STATE_H_
#define _INCLUDED_STATE_H_

#include <iosfwd>
#include <vector>
#include <set>

#include "../statetype/statetype.h"
#include "../next/next.h"
#include "../srconflict/srconflict.h"
#include "../rrconflict/rrconflict.h"

class Item;
class Production;
class StateItem;
class Rules;

class State
{
    typedef std::vector<State *> Vector;
    
    public:
        typedef Vector::const_iterator  ConstIter;

    private:
        friend std::ostream &operator<<(std::ostream &out, 
                                        State const *state); 

        StateItem::Vector   d_itemVector;
    
        size_t              d_nKernelItems;
    
        std::vector<size_t> d_reducible;    // d_itemVector offsets containing
                                            // reducible items
    
        size_t              d_nTransitions; // elements in d_nextVector minus
                                            // removed elements because of
                                            // conflicts
    
        size_t              d_nReductions;  // elements in d_reducible minus
                                            // reductions having empty LA-sets

        size_t              d_defaultReducible; // the d_reducible  index of
                                            // the reduction to use as default
                                            // (or npos)

        size_t              d_maxLAsize;    // the default reduction becomes 
                                            // the one having the largest
                                            // LAset size 

        size_t              d_summedLAsize; // sum of all lookaheadsets of all
                                            // non-default reductions. 

        Next::Vector        d_nextVector;   // Vector of Next elements
                                            // describing where to transit to
                                            // next. 

        size_t              d_idx;          // index of this state in the
                                            // vector of States

        size_t              d_nTerminalTransitions;

        SRConflict          d_srConflict;
        RRConflict          d_rrConflict;
    
        StateType           d_stateType;

        static Vector       s_state;
        static State       *s_acceptState;

        static std::ostream &(State::*s_insert)(std::ostream &out) const;

    public:
        bool isAcceptState() const;
        bool nextContains(Next::ConstIter *iter, 
                          Symbol const *symbol) const;

        size_t idx() const;
        size_t nextOn(Symbol const *token) const;        

            // All reduction members operate with indices in d_reducible,
            // so *not* with d_stateItem indices

        size_t defaultReduction() const;    // def. reduction idx or npos
        StateItem const *reduction(size_t idx) const; // 0 or reduction item

        size_t reductions() const;          // number of reductions
        size_t reductionsLAsize() const;    // summed LA set sizes of all
                                            // non-default reductions

        Symbol const *nextTerminal(size_t *idx) const; 
                                            // Next terminal at 
                                            // d_next[*idx], 0 if none

        size_t terminalTransitions() const;
        size_t transitions() const;
        Next::Vector const &next() const;

        static size_t nStates();

        static void allStates();
                                        // defines all grammar-states and
                                        // lookahead sets
        static void define(Rules const &rules);   

        static ConstIter begin();       // iterator to the first State *
        static ConstIter end();         // and beyond the last

        int type() const;               // StateType accessor

    private:
        State(size_t idx);

        void addDependents(Next const &next, Symbol const *symbol, 
                           size_t itemIdx);
                            // from notreducible from setitems: determine all 
                            // dependent state items and X-link d_itemVector 
                            // and d_nextVector

        void addKernelItem(StateItem const &stateItem);

        void addNext(Symbol const *symbol, size_t idx);
                            // from notreducible from setitems: 
                            // add a new Next element to d_nextVector

        void addState(Item::Vector const &kernel);

        void construct();   // construct a state, and by recursion all other
                            // states as well

        size_t findKernel(Item::Vector const &kernel) const;

        void notReducible(size_t idx);    
                            // handle items in setItems() that aren't 
                            // reducible

        void setItems();    // fill d_itemVector with this state's items 

                            // add the productions of `symbol' to d_itemVector,
                            // make them depend on d_itemVector[idx]
        void addProductions(Symbol const *symbol, size_t idx);

        Next::ConstIter nextFind(Symbol const *symbol) const;

        std::ostream &insertStd(std::ostream &out) const;
        std::ostream &insertExt(std::ostream &out) const;
        std::ostream &skipInsertion(std::ostream &out) const;

        static void initialState();
        static State &newState();

        void nextState(Next &next);
        bool hasKernel(Item::Vector const &kernel) const;
        void checkConflicts();
        void summarizeActions();

        void showSRConflicts(Rules const &rules) const;
        void showRRConflicts(Rules const &rules) const;

        static void determineLAsets();

        void computeLAsets();
        void distributeLAsetOf(StateItem &item);
        void inspectTransitions(std::set<size_t> &todo);
};

inline int State::type() const
{
    return d_stateType.type();
}

inline size_t State::idx() const
{
    return d_idx;
}

inline size_t State::nStates() 
{
    return s_state.size();
}

inline size_t State::terminalTransitions() const
{
    return d_nTerminalTransitions;
}

inline size_t State::transitions() const
{
    return d_nTransitions;
}

inline StateItem const *State::reduction(size_t idx) const
{
    return idx >= d_reducible.size() ? 
                0
            :
                &d_itemVector[d_reducible[idx]];
}

inline size_t State::defaultReduction() const
{
    return d_defaultReducible;
}

inline size_t State::reductions() const
{
    return d_nReductions;
}

inline size_t State::reductionsLAsize() const
{
    return d_summedLAsize;
}

inline State::ConstIter State::begin()
{
    return s_state.begin();
}

inline State::ConstIter State::end()
{
    return s_state.end();
}

inline Next::Vector const &State::next() const
{
    return d_nextVector;
}

inline bool State::isAcceptState() const
{
    return this == s_acceptState;
}

inline bool State::nextContains(Next::ConstIter *iter, 
                                Symbol const *symbol) const
{
    return (*iter = nextFind(symbol)) != d_nextVector.end();
}

inline void State::showSRConflicts(Rules const &rules) const
{
    d_srConflict.showConflicts(rules);
}

inline void State::showRRConflicts(Rules const &rules) const
{
    d_rrConflict.showConflicts(rules);
}

inline std::ostream &operator<<(std::ostream &out, State const *state)
{
    return (state->*State::s_insert)(out);
    // One of: insertStd, insertExt or skipInsertion.
}

#endif
