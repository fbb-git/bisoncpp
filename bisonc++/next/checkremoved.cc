#include "next.ih"

void Next::checkRemoved(ostream &out) const
{
    if (d_symbol != 0)      
        out << ": ";
    else                    // symbols may be removed by the SRConflict
    {                       // resolution process.
        if (d_forced)
            out << " (AUTO REMOVED by S/R resolution): ";
        else
            out << " (removed by precedence): ";
    }
}
