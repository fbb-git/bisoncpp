#include "parser.ih"

void Parser::multiplyDefined(Symbol const *sp)
{
    Terminal::inserter(&Terminal::plainName);
    NonTerminal::inserter(&NonTerminal::plainName);

    lineMsg() << (sp->isTerminal() ? "Terminal " : "Nonterminal ") << 
                    sp  << " multiply defined" << err;
}
