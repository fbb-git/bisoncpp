#include "writer.ih"

// static
void Writer::errorLAset(LAsetVector &laSets, State *sp)
{
    if (sp->type() & StateType::ERR_ITEM)
        sp->errorLAset(laSets);             // insert this State's _error_ 
}                                           // LA set
  








