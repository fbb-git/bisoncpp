#include "parser.ih"

bool Parser::locEl(int nElements, Block &block,AtDollar const &atd)
{
    ostringstream os;
    os << s_locationValueStack << indexToOffset(atd.nr(), nElements) << ')';

    block.replace(atd.pos(), atd.length(), os.str());
    warnForceLSP(atd.lineNr());
    return false;
}
