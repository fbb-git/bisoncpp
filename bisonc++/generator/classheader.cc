#include "generator.ih"

// New members and other facilites may be added to the parser's class header
// after its initial generation. 

// A class header is not rewritten by bisonc++ once it's available

void Generator::classHeader() const
{
    ofstream out;
    ifstream in;

    Exception::open(in,  d_options.classSkeleton()); 
    Exception::open(out, d_options.classHeader()); 

    filter(in, out);    
}
