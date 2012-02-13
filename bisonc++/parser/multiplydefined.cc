#include "parser.ih"

void Parser::multiplyDefined(Symbol const *sp)
{
    Terminal::inserter(&Terminal::plainName);
    NonTerminal::inserter(&NonTerminal::plainName);

    emsg << (sp->isTerminal() ? "Terminal " : "Nonterminal ") << 
                    sp  << " multiply defined" << endl;
}
