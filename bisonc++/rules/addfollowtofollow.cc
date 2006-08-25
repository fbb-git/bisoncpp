#include "rules.ih"

// see the dragon-book, p.189: computing FOLLOW

// 3. Since in A -> aBb (a, b: strings of grammar symbols) or A -> aB I have
//    to compute FOLLOW(B) += FOLLOW(A) (but only if b derives <e>), I start
//    from the end of a production rule. and add, walking backwards, 
//    FOLLOW(A) to that B as long as <e> is in its trailer b. Initally b
//    itself is <e>. Once I see a terminal in b we're done. 

void Rules::addFollowToFollow()
{
    size_t/*unsigned*/ lastCount = 0;
    while (true)
    {
        for_each(d_production.begin(), d_production.end(), &expandFollow);

        NonTerminal::resetCounter();

        for_each(d_nonTerminal.begin(), d_nonTerminal.end(), 
                    &NonTerminal::countFollow);

        if (NonTerminal::counter() == lastCount)
            break;

        lastCount = NonTerminal::counter();
    }
}

