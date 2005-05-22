#include "state.ih"

bool State::mergeLookaheads(State const &source, Symbol const &symbol)
{
    msg() << "Merging lookaheads for symbol " << symbol.display() << ":\n"
            "Destination state:" << info;
    show();

    msg() << "Source state:" << info;
    source.show();

    bool ret = false;

    for         // inspect all kernel items of the current (destination)
    (           // state
        KernelIterator kernelIter = d_kernel.begin(); 
            kernelIter != d_kernel.end();
                ++kernelIter
    )
    {
        if (!kernelIter->beforeDot(symbol))
            continue;                       // skip rules not having . symbol

                                        // Find the lookaheads of the item
                                        // transiting to *kernelIter
        LookaheadSet const &sourceLookaheads = 
                                    source.lookaheadsTo(*kernelIter, symbol);

        unsigned lookaheadSize = kernelIter->lookaheadSetSize();
        kernelIter->merge(sourceLookaheads);

        if (lookaheadSize < kernelIter->lookaheadSetSize())
        {
            msg() << "Expanding the lookahead set of item " << spool;
            kernelIter->show();
            ret = true;
        }
    }
    return ret;
}


