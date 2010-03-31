#include "parser.ih"

void Parser::setStart()
{
    if (d_rules.startRule().size())
        lineMsg() << "%start multiply specified" << err;
    else
        d_rules.setStartRule(d_scanner.YYText());
}

