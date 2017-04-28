#include "writer.ih"

void Writer::transitions(size_t *errorLAidx, Table &table, 
                         Next::Vector const &next)
{
    for (auto &element: next)
        transition(errorLAidx, element, table);
}
