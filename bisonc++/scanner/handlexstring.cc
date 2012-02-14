#include "scanner.ih"

bool Scanner::handleXstring()
{
    size_t pos = min(d_matched.rfind("//"), d_matched.rfind("/*"));

    pos = d_matched.find_last_not_of(" \t", pos);
}
