#include "msg.ih"

void operator<<(ostream &ostrstream, void (*manip)(ostream &str))
{
    (*manip)(ostrstream);
}
