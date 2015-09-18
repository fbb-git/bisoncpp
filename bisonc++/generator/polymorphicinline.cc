#include "generator.hh"

void Generator::polymorphicInline(ostream &out) const
{
    if (not d_options.polymorphic())
        return;

    key(out);

    ifstream in;
    Exception::open(in,  d_options.polymorphicInlineSkeleton()); 
    filter(in, out, false);
}












