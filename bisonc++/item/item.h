#ifndef _INCLUDED_ITEM_
#define _INCLUDED_ITEM_


#include "../production/production.h"
#include "../lookaheadset/lookaheadset.h"
// #include "../rules/rules.h"

class Item
{
    Production const *d_production;

    unsigned                d_dot;
    LookaheadSet            d_lookahead;    

    public:
        Item(Production const *start);      // initial item, starts at the 
                                            // start-production. Dot = 0, 
                                            // Lookahead = EOF
        Item(Item const *item, unsigned dot);
        Item(Production const *prod, unsigned dot, LookaheadSet const &laSet);

            // see State::beforeDot() to read why this function is only called
            // when d_dot > 0
        bool beforeDot(Symbol const &symbol) const
        {
            return d_production->at(d_dot - 1) == &symbol;
        }
        unsigned dot() const
        {
            return d_dot;
        }
        static bool ifBeforeDot(Item const &item, Symbol const &symbol) 
        {
            return item.beforeDot(symbol);
        }
        Item incDot() const
        {
            return Item(this, d_dot + 1);
        }
        LookaheadSet const &lookaheadSet() const
        {
            return d_lookahead;
        }
        unsigned lookaheadSetSize() const
        {
            return d_lookahead.setSize();
        }
        void merge(LookaheadSet const &laSet)
        {
            d_lookahead += laSet;
        }
        bool transitsTo(Item const &other) const;
        Production const &production() const  // &rhs() const
        {
            return *d_production;
        }
        unsigned productionSize() const
        {
            return d_production->size();
        }
        bool hasRightOfDot(Symbol const &symbol) const;
        bool operator==(Item const &other) const;

        void show() const;      // show the rule, dotpos and lookahead set

        static void showKernel(Item const &item); // show a kernel item
};

//        bool operator<(Item const &other) const;


#endif


