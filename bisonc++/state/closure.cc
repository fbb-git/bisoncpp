#include "state.ih"

        // Walk along all states. 

        // For each state, visit all its items (rule, dot, {lookahead})  

        // At each item look for rules having `. N x' where `x' the remainder
        // of the rules.  (x possibly empty).  For each of these rules
        // (below, {LA} means a set of look-ahead terminal tokens):
        // determine {LA} = FIRST(x, {current lookahead}) Then for each
        // of N's rules, add (N -> . rule, {LA}) to the current state.

        // Implementation: 

        // N's rules all receive the same {LA} set, so only N, {LA} needs
        // to be added to the current state. In order to determine
        //          {LA} = FIRST(x, {lookahead})
        // FIRST(x) is determined. If it contains <e>, then <e> is removed and
        // {lookahead} is added (see also ../README.states)
        
        // So:
        //  1. Look for rules having    . N x
        //  2. Determine {f} = FIRST(x).
        //  3. If {f} contains <e>, remove <e> and add {lookahead}
        //  3. Add N {f) to the state. 
        //  4. Repeat this process for all N -> . M rules 


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





