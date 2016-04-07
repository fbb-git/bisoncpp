#include "parser.ih"

void Parser::blkCheck(string const &ruleType, Production const &prod)
{
    (this->*
        (
            ruleType == prod[0].sType() ?
                &Parser::blkAssign
            :
                &Parser::blkErr
        )
    )(ruleType, prod);
}
