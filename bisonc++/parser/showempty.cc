#include "parser.ih"

void Parser::showEmpty() const
{
    if (d_rules.lastProduction().isEmpty())
    {
//        d_rules.setEmptyProduction();
        lineMsg() << "      <empty>" << info;
    }
}
