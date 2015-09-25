#include "scanner.ih"

Scanner::Scanner(std::string const &infile)
:
    ScannerBase(infile, ""),
    d_include(false),
    d_matched(matched()),
    d_inclusionDepth(1)
{
    memset(d_commentChar, 0, 2);

    setTags();

    Arg &arg = Arg::instance();

    string value;
    if (arg.option(&value, "max-inclusion-depth"))
        d_maxDepth = stoul(value);
    else
        d_maxDepth = 10;
}
