#include "rules.ih"

// see the dragon-book, p.189: computing FOLLOW
// I use the following implementation:

// 3. Since in A -> aBb (a, b: strings of grammar symbols) or A -> aB I have
//    to compute FOLLOW(B) += FOLLOW(A) (but only if b derives <e>), I start
//    from the end of a production rule. and add, walking backwards, 
//    FOLLOW(A) to that B as long as <e> is in its trailer b. Initally b
//    itself is <e>. Once I see a terminal in b we're done. 

void Rules::expandFollow(Production *production)
{
    Symbol const *lhs = production->lhs();

    for                         // walk along all elements of the rule's RHS
    (
        auto it = production->rbegin(), end = production->rend(); 
            it != end; 
                ++it
    )
    {
        Symbol *symbol = *it;               // access the current symbol

        if (symbol->isTerminal())           // no <e> derivation at a
            return;                             // terminal symbol

                                            // Only NonTerminals from here...

        if (symbol != lhs)                 
            NonTerminal::downcast(symbol)->addToFollow(
                                               NonTerminal::downcast(lhs)
                                           );

        if (!symbol->firstSet().hasEpsilon())   // no more <e> derivations
            return;
    }
}


