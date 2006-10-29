#include "next.ih"

ostream &Next::insertExt(ostream &out) const
{
    if (!d_symbol)         // symbols may be removed by the SRConflict
        return out;             // resolution process.

    out << "On " << OM::std << symbol() << " to state " << 
           static_cast<int>(d_next) << " with (";

    copy(d_kernel.begin(), d_kernel.end(), 
         ostream_iterator<size_t>(out, " "));

    return out << ")";
}
