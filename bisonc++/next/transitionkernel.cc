#include "next.ih"

ostream &Next::transitionKernel(ostream &out) const
{
    if (!d_symbol)         // symbols may be removed by the SRConflict
        return out;             // resolution process.

    Terminal::inserter(&Terminal::plainName);
    NonTerminal::inserter(&NonTerminal::plainName);

    out << "On " << symbol() << " to state " << 
           static_cast<int>(d_next) << " with (";

    copy(d_kernel.begin(), d_kernel.end(), 
         ostream_iterator<size_t>(out, " "));

    return out << ")";
}
