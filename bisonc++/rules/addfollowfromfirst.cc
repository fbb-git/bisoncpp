#include "rules.ih"

// see the dragon-book, p.189: computing FOLLOW
// I use the following implementation:

// This member inspects one of a nonterminal's production rules, and
//    determines what its implications are to the non-terminal's FOLLOW() set:
// Look for a non-terminal N in this rule: add FIRST(element beyond N) to
//    follow N. This needs to be performed only once, since we'll not change
//    FIRST(X), and therefore: once determined we're done. Furthermore, we'll
//    walk the rule backwards, using a `firstset' that's initally set to
//    FIRST(e) in a rule like A -> aBcde. If d's a non-terminal, then
//    FOLLOW(d) += firstset. Then we add FIRST(d) to firstset, and if c's a
//    non-terminal, we do FOLLOW(c) += firstset, etc. until we reach the
//    rule's begin element. However, firstset is reset to only FIRST(x) if x
//    does not contain <e>.

void Rules::addFollowFromFirst(Production *production)
{
    FirstSet firstSet;

    for 
    (                               // visit each of the production's symbols
        Production::reverse_iterator it = production->rbegin(); 
            it != production->rend(); 
                ++it          // it points at a Production element, 
    )                               // which is a Symbol.
    {
        Symbol *symbol = *it;        
        if (it == production->rbegin())     // first to inspect
        {
            firstSet = symbol->firstSet();
            continue;                           
        }

        if (symbol->isNonTerminal())        // if N: add firstSet
            NonTerminal::downcast(symbol)->addToFollow(firstSet);

        if (symbol->firstSet().hasEpsilon())// if <e> in symbol's firstset:
            firstSet += symbol->firstSet(); // augment firstSet
        else
            firstSet = symbol->firstSet();  // else reset firstSet to the
                                            // current symbol's firstset.
    }
}

