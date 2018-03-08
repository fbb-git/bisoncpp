#include "parser.ih"

// unused `nElements' is required when initializing s_union in data.cc

bool Parser::loc([[maybe_unused]] int nElements, 
                 Block &block, AtDollar const &atd)
{
    block.replace(atd.pos(), atd.length(), s_locationValue);
    warnForceLSP(atd.lineNr());
    return false;
}
