#include "scanner.ih"

Scanner::Scanner(std::string const &infile)
:
    ScannerBase(infile, "-"),
    d_include(false),
    d_matched(matched())
{
    memset(d_commentChar, 0, 2);

//    switch_streams(&d_in, &cerr);

    Arg &arg = Arg::instance();

    d_includeOnly = arg.option(0, "include-only");

    string value;
    if (arg.option(&value, "max-inclusion-depth"))
        d_maxDepth = A2x(value);
    else
        d_maxDepth = 10;
}
