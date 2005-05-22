#include "state.ih"

LookaheadSet const &State::lookaheadsTo(Item const &dest, 
                                        Symbol const &symbol) const
{
            // visit all kernel-Items. If a kernel item transits to dest, then
            // return its LookaheadSet
    for
    (
        KernelConstIter kernelIter = d_kernel.begin();
            kernelIter != d_kernel.end();
                ++kernelIter
    )
    {
        if (kernelIter->transitsTo(dest))  
            return kernelIter->lookaheadSet();
    }

        // If there's no kernel item transiting to dest, then inspect the
        // non-kernel items. See if `symbol' is at the beginning of one of the
        // non-kernel item's production rules. If so, return that
        // nonterminal's lookaheadset
    for
    (
        NonKernelMap::const_iterator nonkernelIter = d_nonKernel.begin();
            nonkernelIter != d_nonKernel.end();
                ++nonkernelIter   
    )
    {
        NonTerminal::ProdVect const &prodvect = 
                                        nonkernelIter->first->productions();
        for     // visit all this non-terminal's productions
        (
            NonTerminal::ProdConstIter iter = prodvect.begin();
                iter != prodvect.end();
                    ++iter
        )
        {
            if ((*iter)->atIdx(0) == &symbol)   // if symbol starts the 
                return nonkernelIter->second;   // production, then return the
                                                // non-kernel's lookaheadset
        }
    }

    msg() << "This should not happen: State::lookaheadsTo() failed" << fatal;
    throw 1;    // not reached, but inserted to prevent the 
                // `control reaches end of non-void function' message
}



