#include "parser.ih"

void Parser::setStart()
{
    if (d_rules.startRule().size())
        lineMsg(emsg) << "%start multiply specified" << endl;
    else
        d_rules.setStartRule(d_scanner.YYText());
}

