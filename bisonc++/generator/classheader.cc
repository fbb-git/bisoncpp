#include "generator.ih"

// New members and other facilites may be added to the parser's class header
// after its initial generation. 

// A class header is not rewritten by bisonc++ once it's available

void Generator::classHeader() const
{
    string const &classHeader = d_options.classHeader();

    if (d_stat.set(classHeader))
    {
                // class-name must match
        warnExisting(classHeader, "class-name", 
                                "^class " + d_options.className() + "\\b");

        warnExisting(classHeader, "baseclass-header", 
                    "^#include \"" + d_options.baseclassHeaderName() + '"');

                // if a namespace was provided: it must be present
        if (not d_options.nameSpace().empty())
            warnExisting(classHeader, "namespace", 
                            "^namespace " + d_options.nameSpace() + "\\b");

        if (d_options.specified("scanner"))
        {
                // the 'scanner' include spec. must be present
            warnExisting(classHeader, "scanner", 
                                "^#include " + d_options.scannerInclude());

                // the 'scanner-class-name must be present
            if (d_options.specified("scanner-class-name"))
                warnExisting(classHeader, "scanner-class-name",
                            "^[[:space:]]*" + 
                                d_options.scannerClassName() + 
                                " d_scanner;");
        }
        else if (d_options.specified("scanner-class-name"))
            wmsg << '`' << classHeader << 
            "': option/directive `scanner-class-name' ignored: "
            " option `scanner' not specified" << endl;

        return;
    }

    ofstream out;
    ifstream in;

    Exception::open(in,  d_options.classSkeleton()); 
    Exception::open(out, d_options.classHeader()); 

    filter(in, out);    
}
