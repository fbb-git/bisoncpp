#include "parser.ih"

bool Parser::vsp(int nElements, Block &block,AtDollar const &atd)
{
    ostringstream os;
    os << s_semanticValueStack << "[" << 
                                indexToOffset(atd.nr(), nElements) << "]";

    block.replace(atd.pos(), atd.length(), os.str());
    return false;
}
