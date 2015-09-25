#include "generator.ih"

bool Generator::conflicts() const
{
    bool ret = false;

    emsg.noLineNr();
    emsg.setLineTag("");

    string const &classHeader = d_options.classHeader();

    if (d_stat.set(classHeader))
    {
                // class-name must match
        ret = errExisting(classHeader, "class-name", 
                                "^class " + d_options.className() + "\\b")
              or ret;

        ret = errExisting(classHeader, "baseclass-header", 
                    "^#include \"" + d_options.baseclassHeaderName() + '"')
              or ret;

                // if a namespace was provided: it must be present
        if (not d_options.nameSpace().empty())
            ret = errExisting(classHeader, "namespace", 
                            "^namespace " + d_options.nameSpace() + "\\b")
                  or ret;

        if (d_options.specified("scanner"))
        {
                // the 'scanner' include spec. must be present
            ret = errExisting(classHeader, "scanner", 
                                "^#include " + d_options.scannerInclude())
                  or ret;

                // the 'scanner-class-name must be present
            if (d_options.specified("scanner-class-name"))
                ret = errExisting(classHeader, "scanner-class-name",
                            "^[[:space:]]*" + 
                                d_options.scannerClassName() + 
                                " d_scanner;") 
                      or ret;
        }
        else if (d_options.specified("scanner-class-name"))
            wmsg << '`' << classHeader << 
            "': option/directive `scanner-class-name' ignored: "
            " option `scanner' not specified" << endl;
    }


    string const &implementationHeader = d_options.implementationHeader();
    if (d_stat.set(implementationHeader))
    {
        ret = errExisting(implementationHeader, "class-header", 
                            "^#include \"" + d_options.classHeader() + '"')
              or ret;

        ret = errExisting(implementationHeader, "class-name", 
                            "\\b" + d_options.className() + "::")
              or ret;

        if (not d_options.nameSpace().empty())
            ret = errExisting(implementationHeader, "namespace", 
                            "^namespace " + d_options.nameSpace() + "\\b")
                  or ret;

        string pattern = "\\b" + d_options.scannerTokenFunction() + "\\b";
        replace(pattern, '(', "\\(");
        replace(pattern, ')', "\\)");

        ret = errExisting(implementationHeader, "scanner-token-function",
                        pattern)
              or ret;
    }

    return ret;
}

