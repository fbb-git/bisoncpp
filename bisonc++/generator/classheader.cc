#include "generator.ih"

// New members and other facilites may be added to the parser's class header
// after its initial generation. 

// A class header is not rewritten by bisonc++ once it's available

void Generator::classHeader() const
{
    string const &classHeader = d_options.classHeader();

    if (d_stat.set(classHeader))        // do not overwrite an existing 
        return;                         // class header file

    ofstream out;
    ifstream in;

    Exception::open(in,  d_options.classSkeleton()); 
    Exception::open(out, classHeader); 

    filter(in, out);    
}
