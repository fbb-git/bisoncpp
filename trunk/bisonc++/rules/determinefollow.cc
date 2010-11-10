#include "rules.ih"

// see the dragon-book, p.189: computing FOLLOW, also see the relevant section
//  in bisonc++'s user guide (algorithm: The FOLLOW Sets)
//
// I use the following implementation:
// 1. Set $ in the start-rule (already done by augmentGrammar())
//

// 2. Look for a non-terminal N in each rule: add FIRST(element beyond N) to
//    follow N. This needs to be performed only once, since FIRST(X) doesn't
//    change and therefore: once determined we're done. Furthermore, I walk
//    the rule backwards, using a `firstset' that's initally set to FIRST(e)
//    in a rule like A -> aBcde. If d's a non-terminal, then FOLLOW(d) +=
//    firstset. Then I add FIRST(d) to firstset, and if c's a non-terminal, I
//    do FOLLOW(c) += firstset, etc. until I reach the rule's begin
//    element. However, firstset is reset to only FIRST(x) if FIRST(x) does 
//    not contain <e>.

//
// 3. Since in A -> aBb (a, b: strings of grammar symbols) or A -> aB I have
//    to compute FOLLOW(B) += FOLLOW(A) but only if b derives <e>, I start
//    from the end of a production rule. and add, walking backwards, 
//    FOLLOW(A) to FOLLOW(B) as long as <e> is in its trailer b. Initally b
//    itself is <e>. Once I see a terminal in b I'm done. 

void Rules::determineFollow()
{
    // inspect each Non-terminal:
    // inspect each of its production rules. Therein: 
    // call a member inspecting one production rule
    for_each(d_nonTerminal.begin(), d_nonTerminal.end(), &addFirstToFollow);

    addFollowToFollow();                                // see 3, above
}
