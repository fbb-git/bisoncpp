#include "parser.ih"

Parser::SemTag Parser::semTag(char const *label, AtDollar const &atd, 
                     bool (Parser::*testID)(std::string const &) const) const
{
    string const &stype = 
        atd.returnValue() ? 
            d_rules.sType()
        :
            d_rules.sType(atd.nr());      // get the rule/element's stype

    string const *id = &atd.id();

    if (atd.nr() < 0)
    {
        negativeIndex(atd);
        return NONE;
    }

        
    if  // with polymorphic: warn if an untyped $-value is used
    (
        d_semType == POLYMORPHIC
        &&
        not atd.returnValue() && stype.empty() && id->empty()
    )
        warnUntaggedValue(atd);


    if (stype.empty() || stype == "STYPE__")    // no rule stype
    {
        if (atd.id().empty())                   // no explicit tag either
            return NONE;
        
        if (atd.id() == "STYPE__")              // no explicit tag requested
            return NONE;
        
        if ((this->*testID)(atd.id()))
            return EXPLICIT;
    }
    else if ((this->*testID)(stype))            // auto tag/field
    {
        if (atd.id().empty())                   // but no explicit tag/field
        {
            if (atd.callsMember())
            {
                warnAutoIgnored(label, atd);
                return NONE;
            }
            return AUTO;
        }
        
        if (atd.id() == "STYPE__")              // ignoring auto tag/field
            return NONE;
        
        if ((this->*testID)(atd.id()))          // tag/field override
        {
            if (d_semType == POLYMORPHIC)
                warnAutoOverride(atd);

            return EXPLICIT;
        }
    }
    else    // stype is illegal
    {
        if (atd.id().empty())                   // no explicit type, but 
            id = &stype;                        // auto is illegal: set ptr.
        else
        {
            if (atd.id() == "STYPE__")          // no explicit tag requested
                return NONE;
            
            if ((this->*testID)(atd.id()))
            {
                if (d_semType == POLYMORPHIC)
                    warnAutoOverride(atd);

                return EXPLICIT;
            }
        }
    }
    
    errNoSemantic(label, atd, *id);
    return NONE;
}
