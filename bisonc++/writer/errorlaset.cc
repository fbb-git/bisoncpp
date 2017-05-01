#include "writer.ih"

// static
void Writer::errorLAset(size_t *idx, State const *sp, std::ostream &out)
{
    if (sp->type() & StateType::ERR_ITEM)
    {
        sp->insertLAset(out);               // insert this State's _error_ 
        out << " // " << ++*idx << '\n';    // LA set
    }
} 








