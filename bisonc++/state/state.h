#ifndef _INCLUDED_STATE_H_
#define _INCLUDED_STATE_H_

#include <vector>
#include <map>

#include "../item/item.h"
#include "../lookaheadset/lookaheadset.h"

#include "../srconflict/srconflict.h"
#include "../rrconflict/rrconflict.h"
#include "../transition/transition.h"

class Production;

class State
{
    public:
        typedef std::map<Symbol const *, Transition *> TransitionMap;
        typedef TransitionMap::value_type              TransitionMapValue;
        typedef TransitionMap::iterator                TransitionMapIterator;
    
    private:
        enum Type           // modify data.cc when this enum changes
        {
            NORMAL,
            HAS_ERROR_ITEM,
            IS_ERROR_STATE
        };    
    
        typedef std::vector<RRConflict> RRConflictVector;
        typedef std::vector<SRConflict> SRConflictVector;
    
        typedef std::vector<State *> StateVector;
        typedef std::vector<Item>    ItemVector;
    
        typedef std::vector<Symbol const *>  NonKernelVector;
    
        typedef std::map<Production const *, LookaheadSet> ReduceMap;
        typedef ReduceMap::value_type                      ReduceMapValue;
        typedef ReduceMap::iterator                        ReduceMapIterator;
    
        static StateVector  s_state;
        static unsigned s_nShiftReduceConflicts;
        static unsigned s_nReduceReduceConflicts;
    
        static char const *s_stateName[];   // ascii-text representations of
                                            // the state types
        static State *s_acceptState;
        static Production const *s_startProduction;
    
        Type                d_type;
        unsigned            d_idx;
    
        ItemVector          d_kernel;
        ReduceMap           d_reduce;
    
        TransitionMap       d_transition;
        NonKernelVector     d_nonKernel;
        bool                d_construct;
        unsigned            d_nTransitions; 
    
        SRConflictVector    d_srConflict;
        RRConflictVector    d_rrConflict;
    
        Production const   *d_defaultReduction;
    
    public:
        typedef TransitionMap::const_iterator   TransitionMapConstIterator;

        State(unsigned idx);

        Production const *defaultReduction() const
        {
            return d_defaultReduction;
        }
        TransitionMap const &transitionMap() const
        {
            return d_transition;
        }

        static void showConflicts();

        static void define(Production const *start);   
                                // define all the grammar-states and
                                // lookaheads 

        bool isAcceptState() const
        {
            return this == s_acceptState;
        }

        static void showAllStates();

        static unsigned nStates()
        {
            return s_state.size();
        }

        static StateVector::const_iterator begin()
        {
            return s_state.begin();
        }
        static StateVector::const_iterator end()
        {
            return s_state.end();
        }
        struct WSAContext                       // writeStateArrayContext
        {
            std::string const &baseclassScope;
            std::ostream &out;
        };

        static void writeStateArray(State const *state, WSAContext &context);

        unsigned idx() const
        {
            return d_idx;
        }
        Symbol const *reductionLhs() const;

    private:
        void addKernelItem(Item const &item);

        static void addKernelItem(Item const &item, State &state)
        {
            state.addKernelItem(item);
        }

        void construct();       // construct all states beyond this state
                                // (without their LA-sets)

                                // Inspect the LA set of a state 
        void defineLookaheads(LookaheadSet const &la);

                                // define actions, reductions and goto's
                                // determine and solve conflicts
        static void defineActions();

        static State &newState();

        static void writeTransition(TransitionMapValue const &transit, 
                            WSAContext &context);
        
        static void writeReduction(ReduceMapValue const &reduction,
                                   std::ostream &out);

        struct WRContext                       // writeReductionContext
        {
            std::ostream &out;
            int nr;
        };
        static void writeReduceAt(Element const *symbol, WRContext &context);

        static void showState(State *state);

        void show();                    // show the state
        void showKernel();
        static void showKernelLA(Item const &item, TransitionMap &transmap);

        static void showNonKernelItem(Symbol const *nonKernel);
        static void showTransition(TransitionMapValue const &transit) ;
        static void showReduction(ReduceMapValue const &reduction);

        void tuneAcceptState();
        static void noShiftOnEOF(TransitionMap::value_type &transit)
        {
            transit.second->rmEOF();
        }

        static void defineStateActions(State *state);
        void solveReduceReduceConflicts();
        static void installLA(ReduceMapValue &reduction, 
                              TransitionMap &transmap);

        struct RRContext
        {
            bool headerDisplayed;
            bool leftReductionDisplayed;

            unsigned idx;
            ReduceMapIterator reduceIter;
        };

        static void compareReductions(ReduceMapValue &first, 
                               RRContext &rrc);

        void solveShiftReduceConflicts();
        struct SRContext
        {
            bool headerDisplayed;
            State &state;
        };
        static void detectSR(TransitionMapValue &, SRContext &src);

        static bool findTerminal(ReduceMapValue const &rmap, 
                                 Symbol &terminal) 
        {
            return rmap.second.count(&terminal);
        }

        static bool solveSRbyPriority(TransitionMapValue &transition, 
                              SRContext &src, ReduceMapIterator &reduceIter);
        static bool solveSRbyAssociation(TransitionMapValue &transition,
                              SRContext &src, ReduceMapIterator &reduceIter);

        Transition *transitionOf(Symbol const *symbol);

                                                // 1 line
        static void handleKernelItem(Item const &item, State &state);
        void handleNonKernelItem(Symbol const *symbol);
        static void handleProduction(Production const *prod, State &state);
        void handle(Item const &item);

        static void constructDestination(TransitionMapValue &transit);
        static void defineDestination(TransitionMapValue &transit, 
                                      State &state);
        static bool findState(unsigned *idx, std::vector<Item> const &kernel);
        static bool searchStateWith(State &state, 
                                    std::vector<Item> const &kernel);

        static bool searchItemIn(Item const &item, State &state);

        struct ItemContext
        {
            State &state;
            LookaheadSet const &la;
        };
        static void inspectKernel(Item const &item, ItemContext &itemContext)
        {
            itemContext.state.expandLookaheads(item.lhs(), itemContext.la);
        }

        static void inspectKernelItem(Item &item, State &state);
        
        void expandLookaheads(Symbol const *lhs, LookaheadSet const &la);

        struct DepSymContext
        {
            State &state;
            LookaheadSet const &lhsLA;
        };

        static void inspectDepSym(Symbol const *depSym, State &state);

        static void propagateLookaheads(TransitionMapValue &transit,
                                TransitionMap &transitionMap);

        // rename to inspectProduction:
        static void inspectLA(Item &item, State &);

        struct LookaheadContext 
        {
            TransitionMap &transitionMap;
            LookaheadSet la;
        };

        static void addLookaheads(Item const &item, 
                                    LookaheadContext &laContext)
        {
            laContext.la += 
                laContext.transitionMap[item.lhs()]->lookaheadSet();
        }
};

#endif




