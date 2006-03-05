#include "parser.ih"

// pos is the position of the second $ in '$$'

bool Parser::defaultReturn(unsigned pos) 
{
    string const &defaultType = d_rules.sType();    // get the rule's default
                                                    // type
                                                    
    if (!defaultType.length())                      // warn if there isn't one
        noDefaultTypeWarning();

    string replacement = s_semanticValue;           // use the semantic value

    if (defaultType.length())                       // augment with %union 
        replacement += "." + defaultType;           // type (if available)

    d_block.replace(pos - 1, 2, replacement);       // replace $$ by semantic
                                                    // value

    return true;                                    // this block uses $$
}
