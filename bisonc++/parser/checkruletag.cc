#include "parser.ih"

string Parser::checkRuleTag(AtDollar const &atd) const
{
    string ret = productionTag(atd.nr());

    if (ret.empty())
    {
        emsg.setLineNr(atd.lineNr());
        emsg << "rule " << &d_rules.lastProduction() << 
                ": " << atd.text() << " requires tagged element" << endl;
    }

    return ret;
}
