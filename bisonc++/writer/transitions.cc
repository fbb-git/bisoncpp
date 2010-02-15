#include "writer.ih"

void Writer::transitions(Table &table, Next::Vector const &next)
{
    for_each(next.begin(), next.end(), 
             FnWrap::unary(transition, table));
}
