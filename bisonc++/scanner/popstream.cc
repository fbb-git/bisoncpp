#include "scanner.ih"

bool Scanner::popStream()
{
    bool ret = ScannerBase::popStream();
    d_inclusionDepth -= ret;
    setTags();
    return ret;
}

