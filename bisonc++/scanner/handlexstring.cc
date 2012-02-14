#include "scanner.ih"

bool Scanner::handleXstring(size_t nRedo)
{
    redo(nRedo);

    if (d_block)
    {
        begin(StartCondition__::block);
        d_block += d_matched.c_str();
        return false;
    }

    begin(StartCondition__::INITIAL);

    if (not d_include)
        return true;

    d_include = false;

    string filename = 
                string("\"<").find(d_matched[0]) == 0 ?
                    Options::undelimit(d_matched)
                :
                    d_matched;

    pushStream(filename);
    return false;
}
