#include "parser.ih"

void Parser::setStart()
{
    if (d_scanner.lex() != Scanner::IDENTIFIER)
        lineMsg() << "`%start IDENTIFIER' expected" << err;
    else if (d_rules.startRule().size())
        lineMsg() << "%start multiply declared" << err;
    else
        d_rules.setStartRule(d_scanner.text());
}

