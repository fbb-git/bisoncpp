#include "parser.ih"

Parser::SemTag Parser::semTagPolymorphic(AtDollar const &atd) const
{
    string const &autoTag = d_rules.sType();        // get the rule's auto tag

    bool explictOK = polymorphicTag(atd.idx());

    if (autoTag.empty())                        // no auto tag
    {
        if (atd.id().empty())                   // no explicit tag either
            return RAW_NOAUTO
        
        if (atd.id() == "STYPE__")              // no explicit tag requested
            return RAW;
        
        return explicitOK ? EXPLICIT_NOAUTO : INVALID_EXPLICIT;
    }
    
    // below here: auto tag has been specified


    if (atd.id().empty())
    {
        if (polymorphicTag(autoTag))
            return AUTO;
        
        errInvalidAuto(atd);
        return INVALID_AUTO;
    }

    if (atd.id() == "STYPE__")              // explicitly no tag requested
        return RAW_OVERRIDE;

    if (explicitOK)
        return atd.id() == autoType ? AUTO | EXPLICIT_OVERRIDE;    

    return EXPLICIT_INVALID;               // no such polymorphic type
}

