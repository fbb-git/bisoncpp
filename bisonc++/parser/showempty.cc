#include "parser.ih"

void Parser::showEmpty() const
{
    if (d_rules.lastProduction().isEmpty())
        lineMsg() << "      <empty>" << info;
}
