#include "scanner.ih"

bool Scanner::handleXstring(size_t nRedo)
{
    redo(nRedo);

    setLineNrs();

    if (d_block)
    {
        begin(StartCondition__::block);
        d_block += d_matched;
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

    if (++d_inclusionDepth > d_maxDepth)
        fmsg << "maximum inclusion depth (" << d_inclusionDepth << ", " <<
                    d_maxDepth << ") exceeded" <<
                noid;

    pushStream(filename);
    setTags();
    return false;
}





