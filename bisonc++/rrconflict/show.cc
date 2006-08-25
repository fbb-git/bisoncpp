#include "rrconflict.ih"

void RRConflict::show(RRConflict const &conflict)
{
    size_t/*unsigned*/ n = conflict.d_laSet.fullSize();

    msg() << nlindent << "On " << conflict.d_laSet << "\n" <<
            incindent << "reduce to `" << conflict.first << 
                                                    "' (earlier rule)\n" <<
            indent  << "instead of `" << conflict.second << "'" <<
            nlindent << "(" << n << " R/R conflict"  << 
                        (n == 1 ? "" : "s") << ")" << info;
    Indent::dec();
}
