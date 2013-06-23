#include "generator.ih"

// New members and other facilites may be added to the parser's class header
// after its initial generation. 

// Writing a base class header may be forced by the --force-class-header
// option. Otherwise, it's not rewritten by bisonc++ once it's available

void Generator::classHeader() const
{
    string const &classHeader = d_options.classHeader();

    if 
    (
        not d_arg.option(0, "force-class-header")
        &&
        d_stat.set(classHeader)
    )
    {
        warnExisting(classHeader, "namespace");
        warnExisting(classHeader, "class-name");
        warnExisting(classHeader, "scanner");
        warnExisting(classHeader, "scanner-class-name");
        
        return;
    }

    ofstream out;
    ifstream in;

    Exception::open(in,  d_options.classSkeleton()); 
    Exception::open(out, d_options.classHeader()); 

    filter(in, out);    
}
