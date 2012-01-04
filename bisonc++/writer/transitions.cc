#include "writer.ih"

void Writer::transitions(Table &table, Next::Vector const &next)
{
    for (auto &element: next)
        transition(element, table);
}
