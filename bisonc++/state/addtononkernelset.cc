#include "state.ih"

bool State::addToNonKernelSet(LookaheadSet *lookahead, NonTerminal const *np) 
{
    NonKernelMap::const_iterator it = d_nonKernel.find(np);
    string const &name = np->name();

    if (it == d_nonKernel.end())
    {
        msg() << "\n"
                "    Adding `" << name << "' to the nonkernel set:" << info;
        return true;
    }
    
    if (it->second >= *lookahead)   // it->second: LookaheadSet
    {
        msg() << "\n"
                "    " << name << "'s LA (" << it->second 
                        << ") already contains " << *lookahead << info;
        return false;
    }

    msg() << "\n"
            "    Adding " << *lookahead << " to " << name << "'s LA (" << 
                                it->second << ")" << info;

    *lookahead += it->second;
    msg() << "    " << name << "'s new lookahead set: " << 
                                                    *lookahead << info;
    return true; 
}

