#include "state.ih"

void State::show()
{
    Indent::clear();
    Indent::inc();

    msg() << "\nState " << d_idx << ":\n" << info;
    showKernel();

    for_each(d_nonKernel.begin(), d_nonKernel.end(),
                                                  State::showNonKernelItem);

    msg() << info;

    for_each(d_transition.begin(), d_transition.end(), showTransition);

    // at the accepting state:
    // show the accept on EOF

    if (this == s_acceptState)
        msg() << indent << "On <EOF> accept, using rule " << s_startProduction
                                                        << info;
    if (!d_defaultReduction)
        for_each(d_reduce.begin(), d_reduce.end(), showReduction);
    else
        msg() << indent << "By default reduce, using rule " << 
                    d_defaultReduction << info;

    unsigned n_SR = d_srConflict.size();

    if (d_nRRConflicts)
    {
        msg() << nlindent << d_nRRConflicts << " Reduce/Reduce conflict" << 
                                   (d_nRRConflicts == 1 ? ":" : "s:") << info;
        Indent::inc();
        for_each(d_rrConflict.begin(), d_rrConflict.end(), RRConflict::show);
        Indent::dec();
    }
    if (n_SR)
    {
        msg() << nlindent << n_SR << " Shift/Reduce conflict" << 
                                        (n_SR == 1 ? ":" : "s:") << info;
        Indent::inc();
        for_each(d_srConflict.begin(), d_srConflict.end(), SRConflict::show);
        Indent::dec();
    }
}

