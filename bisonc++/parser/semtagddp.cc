#include "parser.ih"

Parser::SemTag Parser::semTagDDP() const
{
    string const &autoType = d_rules.sType();       // get the rule's default
                                                    // type

    if (autoType.empty())        // no default type
        return UNTYPED;        

    if (autoType == "STYPE__")   // default is STYPE__ 
        return STYPED;
                                    // existing polymorphic type
    if (d_polymorphic.find(autoType) != d_polymorphic.end())
        return TYPED;
                            
    noSemanticTag(autoType);        // no such polymorphic type

    return UNTYPED;
}
