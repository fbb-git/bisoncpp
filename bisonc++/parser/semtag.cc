#include "parser.ih"

Parser::SemTag Parser::semTag(char const *label, AtDollar const &atd, 
                     bool (Parser::*testID)(std::string const &) const) const
{
    string const &stype = d_rules.sType();      // get the rule's stype

    if (atd.nr() < 0)
    {
        negativeIndex(atd);
        return NONE;
    }

    if (stype.empty() || stype == "STYPE__")    // no rule stype
    {
        if (atd.id().empty())                   // no explicit tag either
            return NONE;
        
        if (atd.id() == "STYPE__")              // no explicit tag requested
            return NONE;
        
        if ((this->*testID)(atd.id()))
            return EXPLICIT;
    }
    else if ((this->*testID)(stype))
    {
        if (atd.id().empty())                   // no explicit tag either
            return AUTO;
        
        if (atd.id() == "STYPE__")              // no explicit tag requested
            return NONE;
        
        if ((this->*testID)(atd.id()))
            return EXPLICIT;
    }
    else    // stype is illegal
    {
        if (atd.id() == "STYPE__")              // no explicit tag requested
            return NONE;
        
        if ((this->*testID)(atd.id()))
            return EXPLICIT;
    }
    
    errNoSemantic(label, atd.id());
    return NONE;
}
