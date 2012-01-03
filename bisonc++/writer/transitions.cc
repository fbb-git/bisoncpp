#include "writer.ih"

void Writer::transitions(Table &table, Next::Vector const &next)
{
    for (auto &element: next)
        transition(element, table);

//    for_each(
//        next.begin(), next.end(), 
//        [&](Next const &next)
//        {
//            transition(next, table);
//        }
//    );
}
