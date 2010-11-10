#include "scanner.ih"

Scanner::Scanner(string const &fname)
:
    d_include(false)
{
    memset(d_commentChar, 0, 2);

    Errno::open(d_in, fname);

    d_fileInfo.push_back(FileInfo(fname, 0));   // for the first pushed
                                                // element `second' is not
                                                // used. For next elements
                                                // `second' stores yylineno
                                                // of the pushed file.
    switch_streams(&d_in, &cerr);

    Arg &arg = Arg::instance();

    d_includeOnly = arg.option(0, "include-only");

    string value;
    if (arg.option(&value, "max-inclusion-depth"))
        d_maxDepth = A2x(value);
    else
        d_maxDepth = 10;
}
