#include "rrconflict.ih"

void RRConflict::show(RRConflict const &conflict)
{
    msg() << nlindent << "On " << conflict.d_laSet << "\n" <<
            incindent << "reduce to (earlier rule) " << conflict.first << "\n" <<
            indentdec << "instead of " << conflict.second << info;
}
