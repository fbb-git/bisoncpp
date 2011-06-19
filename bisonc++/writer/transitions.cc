#include "writer.ih"

void Writer::transitions(Table &table, Next::Vector const &next)
{
    for_each(
        next.begin(), next.end(), 
        [&](Next const &next)
        {
            transition(next, table);
        }
    );
}
