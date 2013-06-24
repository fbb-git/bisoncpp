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
    string const &implementationHeader = d_options.implementationHeader();
    if 
    (
        not d_arg.option(0, "force-implementation-header")
        &&
        d_stat.set(implementationHeader)
    )
    {
        if (not d_options.nameSpace().empty())
            warnExisting(implementationHeader, 
                            "namespace", d_options.nameSpace(),
                            "^namespace " + d_options.nameSpace() + "\\b");

        warnExisting(implementationHeader, "class-name", 
                            d_options.className(),
                            "\\b" + d_options.className() + "::");

        warnExisting(implementationHeader, "class-header", 
                            d_options.classHeader(),
                            "^#include \"" + d_options.classHeader() + '"');

        string pattern = "\\b" + d_options.scannerTokenFunction() + "\\b";
        replace(pattern, '(', "\\(");
        replace(pattern, ')', "\\)");

        warnExisting(implementationHeader, "scanner-token-function",
                        d_options.scannerTokenFunction(), 
                        pattern);
                                
        return;
    }

    ofstream out;
    ifstream in;

    Exception::open(in,  d_options.implementationSkeleton()); 
    Exception::open(out, d_options.implementationHeader()); 

    filter(in, out);    
}
