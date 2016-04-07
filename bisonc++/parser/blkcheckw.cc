#include "parser.ih"

void Parser::blkCheckW(string const &ruleType, Production const &prod)
{
    (this->*
        (
            ruleType == prod[0].sType() ?
                &Parser::blkAssignW
            :
                &Parser::blkErr
        )
    )(ruleType, prod);
}
