#include "state.ih"

        // Walk along all states. 

        // For each state, visit all its items (rule, dot, {lookahead})  

        // At each item look for rules having `. N x' where `x' the remainder
        // of the rules.  (x possibly empty).  For each of these rules:
        // determine {first} = FIRST(x element in {lookahead}) Then for each
        // of N's rules, add (N -> . rule, {first}) to the state.

        // Implementation: 

        // N's rules all have the same {first} set, so only N, {first} needs
        // to be added.  

        // If {first-a} is FIRST(x a) and {first-b} is FIRST(x b), then adding
        // rule-a = (N -> . rule, FIRST(x a)) and rule-b = N -> . rule,
        // FIRST(x b) will either be twice N -> . rule, FIRST(x), if <e> not
        // in FIRST<x> or the same rule (N -> . rule) having also a and b in
        // their lookahead sets will be added. So, in order to determine
        //                      {first} = FIRST(x   element in {lookahead})
        // determine FIRST(x). If it contains <e>, then remove <e> and add
        // {lookahead}.
        
        // So:
        //  1. Look for rules having    . N x
        //  2. Determine {f} = FIRST(x), add {lookahead} to FIRST(x). if 
        //                    {lookahead} contains <e>, remove <e>
        //  3. Add N FIRST(x, {f) to the state. 
        //  4. Do this also for N -> . M rules 

        // if N has an empty production, then look also for rules . N P x
        // for these, 
        //  2a. Determine {f} = FIRST(x), add {lookahead} to FIRST(x). if 
        //                    {lookahead} contains <e>, remove <e>
        //  3. Add P FIRST(x, {f) to the state. 
        //  4. Do this also for P -> . L rules 


void State::closure() 
{
    for             // inspect all productions in the current itemset 
    (               // (i.e., state)
        KernelIterator itemIt = d_kernel.begin();
            itemIt != d_kernel.end();
                ++itemIt
    )
    {
        msg() << "\n"
                "Computing the closure for" << spool;
        itemIt->show();
        inspectProduction(itemIt->production(), itemIt->dot(), 
                          itemIt->lookaheadSet());
    }
        // display what non-kernel rules we've found:
    showNonKernel();

    msg() << "Closure computed." << info;
}





