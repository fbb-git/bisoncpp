#include "parser.ih"

void Parser::multiplyDefined(Symbol const *sp)
{
    lineMsg() << (sp->isTerminal() ? "Terminal " : "Nonterminal ") << 
                    OM::std << sp  << " multiply defined" << err;
}
