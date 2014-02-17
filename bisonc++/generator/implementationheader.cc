#include "generator.ih"

// All members of the parser class should include the implementation header as
// the only #included file. The implementation header should perform all
// required preprocessor actions for the compilation of the Parser's class
// members

// The implementation header header is not rewritten by
// bisonc++ once it's available

void Generator::implementationHeader() const
{
    string const &implementationHeader = d_options.implementationHeader();

    if (d_stat.set(implementationHeader))   // do not overwrite an existing
        return;                             // implementation header

    ofstream out;
    ifstream in;

    Exception::open(in,  d_options.implementationSkeleton()); 
    Exception::open(out, implementationHeader); 

    filter(in, out);    
}
