#include "generator.ih"

void Generator::baseclassHeader() const
{
    if (Arg::getInstance().option(0, "no-baseclass-header"))
        return;

    ofstream out;
    ifstream in;

    Msg::open(in,  d_parser.baseclassSkeleton()); 
    Msg::open(out, d_parser.baseclassHeader()); 

    filter(in, out);    
}
