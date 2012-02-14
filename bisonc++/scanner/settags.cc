#include "scanner.ih"

void Scanner::setTags() const
{
    emsg.setTag(filename() + ": error");
    fmsg.setTag(filename() + ": fatal");
    imsg.setTag(filename() + " (info)");
    wmsg.setTag(filename() + ": warning");
    setLineNrs();
}
