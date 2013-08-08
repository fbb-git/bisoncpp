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
                // class-name must match
        warnExisting(classHeader, "class-name", d_options.className(),
                                "^class " + d_options.className() + "\\b");

        warnExisting(classHeader, "baseclass-header", 
                    d_options.baseclassHeaderName(), 
                    "^#include \"" + d_options.baseclassHeaderName() + '"');

                // if a namespace was provided: it must be present
        if (not d_options.nameSpace().empty())
            warnExisting(classHeader, "namespace", d_options.nameSpace(),
                            "^namespace " + d_options.nameSpace() + "\\b");

        if (d_options.specified("scanner"))
        {
                // the 'scanner' include spec. must be present
            warnExisting(classHeader, "scanner", d_options.scannerInclude(), 
                                "^#include " + d_options.scannerInclude());

                // the 'scanner-class-name must be present
            warnExisting(classHeader, "scanner-class-name",
                            d_options.scannerClassName(), 
                            "^[[:space:]]*" + 
                                d_options.scannerClassName() + 
                                " d_scanner;");
        }

        return;
    }

    ofstream out;
    ifstream in;

    Exception::open(in,  d_options.classSkeleton()); 
    Exception::open(out, d_options.classHeader()); 

    filter(in, out);    
}
