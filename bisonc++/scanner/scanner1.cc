#include "scanner.ih"

Scanner::Scanner(std::string const &infile)
:
    ScannerBase(infile, ""),
    d_include(false),
    d_matched(matched())
{
    memset(d_commentChar, 0, 2);

    Arg &arg = Arg::instance();

    string value;
    if (arg.option(&value, "max-inclusion-depth"))
        d_maxDepth = A2x(value);
    else
        d_maxDepth = 10;
}
