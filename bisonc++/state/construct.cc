#include "state.ih"

void State::construct() 
{
    if (!d_construct)
        return;

    d_construct = false;

    Indent::clear();
    Indent::inc();
    
    msg() << "\n"
            "Constructing state " << d_idx << info;

    if (d_kernel.size())
    {
        msg() << nlindent << "Handling KERNEL items" << info;
        for_each(d_kernel.begin(), d_kernel.end(),
            Wrap1c<Item, State>(handleKernelItem, *this));
    }
    
    if (d_nonKernel.size())
    {
        msg() << nlindent << "Handling NON-KERNEL items" << info;
        for (size_t/*unsigned*/ idx = 0; idx < d_nonKernel.size(); ++idx)
            handleNonKernelItem(d_nonKernel[idx]);
    }        

    if (d_transition.size() > 1)
    {
        msg() << nlindent << "Destination states" << info;
        Indent::inc();
        for_each(d_transition.begin(), d_transition.end(),
            Wrap1c<TransitionMapValue, State>
                    (defineDestination, *this));        
        Indent::dec();

        for_each(d_transition.begin(), d_transition.end(),
                constructDestination);
    }

    msg() << "\n"
            "State " << d_idx << " constructed" << info;
}


