#include "parser.ih"

void Parser::defaultPolymorphicAction()
{
    Options::Value actionType = d_options.defaultActions().value;
    
    if (actionType == Options::OFF)     // no default action block if 
        return;                         //  suppressed

    Production const &prod = d_rules.lastProduction();
    
    if (prod.size() == 0)               // empty production rule
    {
        if (actionType == Options::WARN)
            warnDefaultAction(prod);

        installDefaultAction(prod, s_stype + "{}");
        return;
    }
                                        // semantic value of the rule's rhs
    string const &ruleType = d_rules.sType();
    
                                        // try to add a default action block
    (this->*s_defaultAction             
            [actionType == Options::WARN]   // 0: action block w/o warning
            [ typeIndex(ruleType)]
            [ typeIndex( prod[0].sType() ) ])(ruleType, prod);
}





