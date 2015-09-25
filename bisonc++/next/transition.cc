#include "next.ih"

// -----------------------------------------
//                 d_removed
//             -----------------------------
// d_symbol    0             not 0
// -----------------------------------------
//     0       item          item removed by
//             removed       SR resolution
//                           in favor of
//                           Reduce  
//   not 0     item active   does not happen
// -----------------------------------------

std::ostream &Next::transition(std::ostream &out) const
{
    checkRemoved(out);

    out << "  On ";
    Symbol const *ps = pSymbol();
    if (ps)
        out << ps;
    else
        out << "????";

    out << " to state " << 
                                                static_cast<int>(d_next);
    return out;
//
//    return out << "  On " 
////<< pSymbol() 
//<< " to state " << 
//                                                static_cast<int>(d_next);
}
