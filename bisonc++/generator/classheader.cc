#include "generator.ih"

void Generator::classHeader() const
{
    if 
    (
        access(d_parser.classHeader().c_str(), F_OK) == 0
        &&
        not Arg::instance().option(0, "force-class-header")
    )
        return;

    ofstream out;
    ifstream in;

    Msg::open(in,  d_parser.classSkeleton()); 
    Msg::open(out, d_parser.classHeader()); 

    filter(in, out);    
}
