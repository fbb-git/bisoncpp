#include "parser.ih"

// pos is the position of the second $ in '$$'

bool Parser::defaultReturn(size_t pos, Block &block) 
{
    string const &defaultType = d_rules.sType();    // get the rule's default
                                                    // type
                                                    
    if (!defaultType.length())                      // warn if there isn't one
        noDefaultTypeWarning();

    string replacement = s_semanticValue;           // use the semantic value

    if (defaultType.length())                       // augment with
    {                                               // %union field or
        if (d_semType == UNION)                     // %polymorphic type
            replacement += "." + defaultType;
        else if (not callsMember(block, pos)) 
        {
            if (d_polymorphic.find(defaultType) != d_polymorphic.end())
                replacement += ".get<" + defaultType + ">()";
            else
                emsg << "no such polymorphic semantic value identifier `" <<
                        defaultType << '\'';
        }
    }

    block.replace(pos - 1, 2, replacement);
                                                    // replace $$ by semantic
                                                    // value

    return true;                                    // this block uses $$
}
