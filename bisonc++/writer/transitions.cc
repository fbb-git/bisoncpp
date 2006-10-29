#include "writer.ih"

void Writer::transitions(Next::Vector const &next, ostream &out)
{
    for_each(next.begin(), next.end(), 
             Wrap1c<Next, ostream>(transition, out));
}
