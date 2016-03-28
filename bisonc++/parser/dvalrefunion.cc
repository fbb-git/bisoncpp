#include "parser.ih"

    // $$
bool Parser::dvalRefUnion(int nElements, Block &block, AtDollar const &atd)
{
    return 
        (this->*
            (atd.refByScanner() ?
                &Parser::dvalUnionReplace
            :
                &Parser::dvalReplace
            )
        )(block, atd, "");
}
