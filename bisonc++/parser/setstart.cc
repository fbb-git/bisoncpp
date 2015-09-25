#include "parser.ih"

void Parser::setStart()
{
    if (d_rules.startRule().size())
        emsg << "%start multiply specified" << endl;
    else
        d_rules.setStartRule(d_matched);
}

