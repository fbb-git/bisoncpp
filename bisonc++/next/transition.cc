#include "next.ih"

std::ostream &Next::transition(std::ostream &out) const
{
    if (!d_symbol)         // symbols may be removed by the SRConflict
        return out;        // resolution process.

    return 
        out << "  On " << symbol() << " to state " << 
                                                static_cast<int>(d_next);
}
