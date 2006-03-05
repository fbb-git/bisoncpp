#include "generator.ih"

void Generator::implementationHeader() const
{
    if 
    (
        access(d_parser.implementationHeader().c_str(), F_OK) == 0
        &&
        not Arg::instance().option(0, "force-implementation-header")
    )
        return;

    ofstream out;
    ifstream in;

    Msg::open(in,  d_parser.implementationSkeleton()); 
    Msg::open(out, d_parser.implementationHeader()); 

    filter(in, out);    
}
