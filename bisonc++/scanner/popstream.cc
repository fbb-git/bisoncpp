#include "scanner.hh"

bool Scanner::popStream()
{
    bool ret = ScannerBase::popStream();
    d_inclusionDepth -= ret;
    setTags();
    return ret;
}

