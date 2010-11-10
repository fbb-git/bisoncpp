#include "generator.ih"

// All members of the parser class should include the implementation header as
// the only #included file. The implementation header should perform all
// required preprocessor actions for the compilation of the Parser's class
// members

// Writing an implementation header header may be forced by the
// --force-implementation-header option. Otherwise, it's not rewritten by
// bisonc++ once it's available

void Generator::implementationHeader() const
{
    if 
    (
        access(d_parser.implementationHeader().c_str(), F_OK) == 0
        &&
        not d_arg.option(0, "force-implementation-header")
    )
        return;

    ofstream out;
    ifstream in;

    Errno::open(in,  d_parser.implementationSkeleton()); 
    Errno::open(out, d_parser.implementationHeader()); 

    filter(in, out);    
}
