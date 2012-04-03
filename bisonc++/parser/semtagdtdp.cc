#include "parser.ih"

    // A specific type was provided (as in $<TYPE>$)

Parser::SemTag Parser::semTagDTDP(string const &tagName) const
{
    string const &autoTag = d_rules.sType();    // get the rule's auto tag

    if (autoTag.empty())
    {
        warnNoAuto("type");
        return semTagDTaux(tagName);
    }

    if (autoTag == "STYPE__")
        return semTagDTaux(tagName);

    if (d_polymorphic.find(tagName) == d_polymorphic.end())
    {
        noSemanticTag(tagName);
        return UNTYPED;
    }

    return tagName == autoTag ? TYPED : DELTATYPED;
}



