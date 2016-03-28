#include "parser.ih"

    // $$
bool Parser::dval(int nElements, Block &block, AtDollar const &atd)
{
    return 
        (this->*
            (d_semType == UNION && atd.refByScanner() ?
                &Parser::dvalUnionReplace
            :
                &Parser::dvalReplace
            )
        )(block, atd, "");
}
