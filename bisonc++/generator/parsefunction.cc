#include "generator.ih"

// The parser's parse() member defines the S/R parsing algorithm as well as
// the parsing tables. 

// Writing the parse() member may be prevented by the --no-parse-member
// option. Otherwise, it's rewritten each time bisonc++ is called to process a
// grammar. Providing the --no-parse-member option should not be
// necessary, as it contains the essential information about the
// grammar. Calling bisonc++ with the --no-parse-member basically renders the
// call useless.

void Generator::parseFunction() const
{
    if (d_arg.option(0, "no-parse-member"))
        return;

    ofstream out;
    ifstream in;

    Exception::open(in,  d_options.parseSkeleton()); 
    Exception::open(out, d_options.parseSource()); 

    filter(in, out);    
}
