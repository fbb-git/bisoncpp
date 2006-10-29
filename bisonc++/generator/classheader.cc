#include "generator.ih"

// New members and other facilites may be added to the parser's class header
// after its initial generation. 

// Writing a base class header may be forced by the --force-class-header
// option. Otherwise, it's not rewritten by bisonc++ once it's available

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
