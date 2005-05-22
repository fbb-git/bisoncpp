#include "parser.ih"

unsigned Parser::blockReturn(string *replacement, unsigned pos) 
{
    string const &defaultType = d_rules.sType();

    string typeSpec;        // get an explicit type if available
    unsigned length = extractType(&typeSpec, pos);

                            // warn if the rule has no associated type
    if (typeSpec.length() && !defaultType.length())
        lineMsg() << "$$ of `" << d_rules.name() << 
                                "' has no default type-association" << 
                                warning;

    *replacement = s_semanticValue;

    string const &type =    typeSpec.length() ? typeSpec : defaultType;

    if (type.length())
        *replacement += "." + type;

    return length;
}
