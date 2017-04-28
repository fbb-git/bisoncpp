#include "writer.ih"

// static
void Writer::errorLAset(State const *sp, std::ostream &out)
{
    if (not (sp->type() & StateType::ERR_ITEM))
        return;

    sp->insertLAset(out);
}








