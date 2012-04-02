#include "parser.ih"

    // A specific field was provided (as in $<TYPE>$)

Parser::SemTag Parser::semTagDTDU(string const &unionField) const
{
    string const &autoField = d_rules.sType();    // get the rule's auto field

    if (autoField.empty())                  // no auto field association
        return unionField.length() ? DELTATYPED : UNTYPED:

    if (autoField == unionField)        // auto type was requested
        return TYPED;
                                            // try to override the auto field
    return unionField.empty() ? TYPED : DELTATYPED;
}
