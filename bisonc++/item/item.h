#ifndef _INCLUDED_ITEM_
#define _INCLUDED_ITEM_


#include "../production/production.h"
#include "../lookaheadset/lookaheadset.h"

class Item
{
    Production const *d_production;

    unsigned                d_dot;

    public:
        Item(Production const *start);      // initial item, starts at the 
                                            // start-production. Dot = 0, 
                                            // Lookahead = EOF

        Item(Item const *item, unsigned dot);

        Item(Production const *prod, unsigned dot);
                                        //, LookaheadSet const &laSet);

            // see State::beforeDot() to read why this function is only called
            // when d_dot > 0
        Symbol const *dotSymbol() const         // symbol at the dot (must 
        {                                       // exist!)
            return &(*d_production)[d_dot];
        }

        Symbol const *dotSymbolOr0() const      // symbol at the dot or 0
        {                                       // if dot at end of production
            return d_dot == d_production->size() ?
                        0
                    :
                        dotSymbol();
        }

        Symbol const *symbolBeforeDot() const      // symbol before the dot
        {
            return &(*d_production)[d_dot - 1];
        }

        unsigned dot() const
        {
            return d_dot;
        }

        Item incDot() const
        {
            return Item(this, d_dot + 1);
        }
        bool transitsTo(Item const &other) const;
        Production const &production() const  // &rhs() const
        {
            return *d_production;
        }

        LookaheadSet lookaheadFromDot(LookaheadSet const &laSet) const;

        Symbol const *lhs() const
        {
            return d_production->lhs();
        }

        bool reduce() const             // if dot at end
        {
            return d_dot == productionSize();
        }
        bool empty() const              // if no size
        {
            return productionSize() == 0;
        }

        unsigned productionSize() const
        {
            return d_production->size();
        }
        bool hasRightOfDot(Symbol const &symbol) const;
        bool operator==(Item const &other) const;

        void show() const;      // show the rule and dotpos

        static void showKernel(Item const &item,
                                char const *end = ")"); // show a kernel item
};

#endif
