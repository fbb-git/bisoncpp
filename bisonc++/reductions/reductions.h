#ifndef _INCLUDED_REDUCTIONS_
#define _INCLUDED_REDUCTIONS_

#include <vector>
#include <iterator>

class Symbol;
class Production;

class Reductions
{
    unsigned d_count;               // number of reductions inserted
    unsigned d_nTokens;             // number of non-default transitions
                                    // used in this state
    unsigned d_defaultReduction;    // INDEX of the default transition

    typedef std::vector<Symbol const *> SymbolVector;
                                    // vector of tokens used for this
                                    // transition
    class Transition: public SymbolVector
    {
        int d_nr;                   // production rule to reduce to
        bool d_default_;            // this one is used for the _default_
                                    // token
        public:
            Transition()
            :
                d_nr(INT_MAX),
                d_default_(false)
            {}
            Transition(unsigned prodNr);
            void setDefault(bool value = true)
            {
                d_default_ = value;
            }
            unsigned uNr() const
            {
                return d_nr;
            }
            int nr() const
            {
                return d_nr;
            }
            bool isDefault() const
            {
                return d_default_;
            }
    };

    typedef std::vector<Transition> TransitionVector;
    TransitionVector d_transitions;

    public:
        typedef std::pair<Symbol const *, int> Pair;

        class iterator: public 
                        std::iterator<std::input_iterator_tag, Pair>
        {
            friend class Reductions;

            TransitionVector::const_iterator d_transition;
                                    // iterator into its symbols
            SymbolVector::const_iterator d_symbol;
            

            public:
                bool operator!=(iterator const &rhs) const
                {
                    return d_transition != rhs.d_transition;
                }
                iterator &operator++();
                Pair const operator*() const
                {
                    return Pair(*d_symbol, -d_transition->nr());
                }

            private:
                iterator(TransitionVector::const_iterator const &begin, 
                         SymbolVector::const_iterator const &symbol)
                :
                    d_transition(begin),
                    d_symbol(symbol)
                {}

                iterator(TransitionVector::const_iterator const &end)
                :
                    d_transition(end)
                {}
                    
        };
            
        iterator const begin() const;
        iterator const end() const;

        Reductions();

                    // Symbol actually is a Terminal.
        void insert(Symbol const *tp, Production const *production);

        unsigned count() const
        {
            return d_count;
        }

        unsigned used() const
        {
            return d_transitions.size() - hasDefaultReduction();
        }

        bool hasDefaultReduction() const
        {
            return d_defaultReduction < d_transitions.size();
        }

        int defaultReduction() const
        {
            return d_transitions[d_defaultReduction].nr();
        }

        void setDefault();

    private:
        static bool findProduction(Transition &trans, unsigned &nr)
        {
            return trans.uNr() == nr;
        }

        struct MaxTransition
        {
            unsigned max;
            Transition *maxTrans;
        };
        static void maxTransition(Transition &trans, MaxTransition &context);

};
        
#endif
