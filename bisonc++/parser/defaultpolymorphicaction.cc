#include "parser.ih"

void Parser::defaultPolymorphicAction(Production const &prod)
{
    Options::Value actionType = d_options.defaultActions().value;
    
    if (actionType == Options::OFF)     // no default action block if 
        return;                         //  suppressed

                                        // semantic value of the rule's rhs
    string const &ruleType = d_rules.sType();

                                        // try to add a default action block
    (this->*s_defaultAction             
            [actionType == Options::WARN]   // 0: action block w/o warning
            [ typeIndex(ruleType)]
            [ typeIndex( prod[0].sType() ) ])(ruleType, prod);
}





