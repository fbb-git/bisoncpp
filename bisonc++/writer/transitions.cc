#include "writer.ih"

void Writer::transitions(Table &table, Next::Vector const &next)
{
    for_each(next.begin(), next.end(), 
             FnWrap1c<Next const &, Table &>(transition, table));
}
