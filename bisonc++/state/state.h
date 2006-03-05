#ifndef _INCLUDED_STATE_
#define _INCLUDED_STATE_

#include <vector>
#include <map>
#include <ostream>

#include "../terminal/terminal.h"
#include "../item/item.h"
#include "../firstset/firstset.h"
#include "../shiftreduce/shiftreduce.h"

class NonTerminal;
class LookaheadSet;

class State
{
    enum Action
    {
        CONFLICT,
        SHIFT_TOKEN,
        REDUCE_RULE
    };
    enum Type           // modify data.cc when this enum changes
    {
        NORMAL,
        HAS_ERROR_ITEM,
        IS_ERROR_STATE
    };    

    typedef std::vector<Item>::iterator 
            KernelIterator;
    typedef std::map<NonTerminal const *, LookaheadSet>
            NonKernelMap;
    typedef NonKernelMap::value_type 
            NonKernelValue;

    struct IIContext                        // inspectItemContext
    {
        State *dest;
        Symbol const &symbol;
    };

    struct AISA0Context                    // addIfSymbolAt0Context
    {
        State *dest;
        Symbol const &symbol;
        LookaheadSet const &lookaheadSet;
    };

    struct MDORContext                      // midDotOrReduceContext
    {
        bool *onlyTrailingDots;
        State &obj;
    };
    
    public:
        typedef std::map<Terminal const *, ShiftReduce>
                ActionTable;
        typedef ActionTable::iterator 
                ActionTableIter;
        typedef ActionTable::const_iterator 
                ActionTableConstIter;
        typedef std::pair<ActionTableConstIter, ActionTableConstIter>
                ActionConstIterators;

        typedef std::map<NonTerminal const *, unsigned>
                GoToTable;
        typedef GoToTable::const_iterator 
                GoToTableConstIter;
        typedef std::set<Symbol const *>
                GoToSet;

    private:
        std::vector<Item>   d_kernel;
        NonKernelMap        d_nonKernel;
                          
        GoToTable           d_goto;             //goto table
        ActionTable         d_action;           // action table
        ActionTable         d_suppressed;       // suppressed actions due to
                                                // default conflict resolution
                          
        GoToSet             d_gotoSet; // first elements of this state's
                                        // production rules. Used
                                        // to determine the GoTos from this
                                        // state, in combination with the
                                        // kernel-state elements beyond the
                                        // dot-positions.
                          
        Terminal const     *d_inheritedTerminal;
        Type                d_type;
        mutable Production const   *d_defaultReduction;
    
        unsigned            d_nShiftReduceConflicts;           
        unsigned            d_nReduceReduceConflicts;           
        unsigned            d_idx;
    
        static unsigned s_acceptingState;
        static unsigned s_nShiftReduceConflicts;
        static unsigned s_nReduceReduceConflicts;
        static char const *s_stateName[];   // ascii-text representations of
                                            // the state types

    public:
        typedef std::vector<Item>::const_iterator 
                KernelConstIter;
        typedef GoToSet::const_iterator
                GoToSetConstIter;

        struct WSAContext                       // writeStateArrayContext
        {
            std::string const &baseclassScope;
            std::ostream &out;
        };

        State();
        State(Item const &item);

        ActionConstIterators actionConstIterators() const
        {
            return ActionConstIterators
                            (d_action.begin(), d_action.end());
        }

        static unsigned acceptingState()
        {
            return s_acceptingState;
        }
        bool acceptState() const
        {
            return d_idx == s_acceptingState;
        }

        bool beforeDot(Symbol const &symbol) const;
        void closure(); 

        unsigned gotoState(NonTerminal const *nonTerminal) const;
        std::set<Symbol const *> const &gotoSet() const
        {
            return d_gotoSet;
        }
        void incDot(State *dest, Symbol const &symbol) const;
        unsigned kernelSize() const
        {
            return d_kernel.size();
        }
        bool mergeLookaheads(State const &state, Symbol const &symbol);
        bool onlyTrailingDotItems();
        bool operator==(State const &other) const
        {
            return d_kernel == other.d_kernel;
        }
        void setErrorState()
        {
            d_type = IS_ERROR_STATE;
        }
        void setIdx(unsigned idx)
        {
            d_idx = idx;
        }
        void setGoto(NonTerminal const *nonTerminal, unsigned nextStateIdx)
        {
            d_goto.insert
            (
                GoToTable::value_type(nonTerminal, nextStateIdx)
            );
        }
        void setShift(Terminal const *token, unsigned nextStateIdx);
        void setShiftTerminal(Symbol const &inheritedTerminal)
        {
            d_inheritedTerminal = Terminal::downcast(&inheritedTerminal);
        }
        void setShiftTerminal(State const &state)
        {
            d_inheritedTerminal = state.d_inheritedTerminal;
        }
        void show() const;          // show the state

        static void showStateConflicts(State const *pState);

        static void showConflicts();

        void showKernel() const;

        static void showTables(State const *state);

        Terminal const *inheritedTerminal() const
        {
            return d_inheritedTerminal;
        }

        Production const *defaultReduction() const
        {
            return d_defaultReduction;
        }

        static void writeStateArray(State const *state, WSAContext &context);
    private:
        static void addIfSymbolAt0(Production const *production, 
                            AISA0Context &context);
        
        void addImpliedNonterminals(NonTerminal const *nonterm, 
                                    LookaheadSet const &firstSet);

        bool addToNonKernelSet(LookaheadSet *lookahead, 
                               NonTerminal const *nonterm);

        static void inspectItem(Item const &item, IIContext &context);

        static void inspectNonKernelProductions(
                        NonKernelValue const &nonKernelIter,
                        IIContext &context);

        void inspectProduction(Production const &production, unsigned dot,
                        LookaheadSet const &lookaheadSet);

        void findFirst(LookaheadSet *firstSet, 
                      Production::const_iterator begin,
                      Production::const_iterator const &end, 
                      LookaheadSet const &lookahead) const;

        LookaheadSet const &lookaheadsTo(Item const &dest, 
                                         Symbol const &symbol) const;

        static void midDotOrReduce(Item &item, MDORContext &context);

        void operator+=(Item const &item);
        void reduce(Item const &item);
        void reduce(Production const *production, 
                    LookaheadSet const &lookaheadSet);

        void setReduce(Terminal const *token, Production const *production);
        void shiftReduceConflict(std::string const &tokenName, 
                                unsigned nextStateIdx,
                                Production const *production);

        void showAction(Terminal const *terminal, ShiftReduce const &action,
                                                  bool block = false) const;
        void showActions() const;
        void showGoTo() const;
        void showNonKernel() const;     
        void showSuppressed() const;

        static void showNonKernelItem(NonKernelValue const &nonKernel);

};

#endif

