#include "generator.ih"

void Generator::polymorphicInline(ostream &out) const
{
    if (not d_options.polymorphic())
        return;

    key(out);

    ifstream in;
    Errno::open(in,  d_options.polymorphicInlineSkeleton()); 
    filter(in, out, false);
}












