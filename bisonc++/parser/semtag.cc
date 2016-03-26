#include "parser.ih"

Parser::SemTag Parser::semTag(char const *label, AtDollar const &atd, 
                     bool (Parser::*testID)(std::string const &) const) const
{
    string const &stype = 
        atd.dollarDollar() ? 
            d_rules.sType()
        :
            d_rules.sType(atd.nr());      // get the rule/element's stype

    string const *tag = &atd.tag();

    if (atd.nr() < 0)
    {
        negativeIndex(atd);
        return NONE;
    }

        
    if  // with polymorphic: warn if an untyped $-value is used
    (
        d_semType == POLYMORPHIC
        &&                                       //tag->empty()
        not atd.dollarDollar() && stype.empty()
    )
        warnUntaggedValue(atd);


    if (stype.empty() || stype == s_stype__)    // no rule stype
    {
        if (atd.tag().empty())                   // no explicit tag either
            return NONE;
        
        if ((this->*testID)(atd.tag()))
            return EXPLICIT;
    }
    else if ((this->*testID)(stype))            // auto tag/field
    {
        if (atd.tag().empty())                   // but no explicit tag/field
        {
            if (atd.callsMember())
            {
                warnAutoIgnored(label, atd);
                return NONE;
            }
            return AUTO;
        }
        
        if ((this->*testID)(atd.tag()))          // tag/field override
        {
            if (d_semType == POLYMORPHIC)
                warnAutoOverride(atd);

            return EXPLICIT;
        }
    }
    else    // illegal stype
    {
        if (atd.tag().empty())                   // no explicit type, but 
            tag = &stype;                        // auto is illegal: set ptr.
        else if ((this->*testID)(atd.tag()))
        {
            if (d_semType == POLYMORPHIC)
                warnAutoOverride(atd);

            return EXPLICIT;
        }
    }
    
    errNoSemantic(label, atd, *tag);
    return NONE;
}
