#include "generator.ih"

void Generator::parseFunction() const
{
    if (Arg::instance().option(0, "no-parse-member"))
        return;

    ofstream out;
    ifstream in;

    Msg::open(in,  d_parser.parseSkeleton()); 
    Msg::open(out, d_parser.parseSource()); 

    filter(in, out);    
}
