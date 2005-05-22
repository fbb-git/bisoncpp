#include "state.ih"

void State::showNonKernel() const
{
    if (d_nonKernel.size())
    {    
        msg() << "    All production rules (using dot == 0) of:" << info;

        for                         // first: nonterminal
        (                           // second: associated LookaheadSet
            NonKernelMap::const_iterator it = d_nonKernel.begin();
                it != d_nonKernel.end();
                    ++it
        )
        {
            string const &name = it->first->name();
            msg() << "      " << name << right <<
                    setw(max(8 - static_cast<int>(name.length()), 1)) << 
                    " " << "Lookahead set " << it->second << info;
        }
        msg() << info;
    }
}
