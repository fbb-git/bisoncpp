#include "parser.ih"

// pos points at the 2nd $ in '$<type>$'

bool Parser::explicitReturn(size_t pos, Block &block) 
{
    size_t dollar1 = block.find_last_of("$", pos - 1);

                                // no first $ or no $<
    if (dollar1 == string::npos || block[dollar1 + 1] != '<')
        throw 1;                // incomplete $-specification

    string typeSpec;        // get the explicit type
    extractType(&typeSpec, dollar1 + 1, block);

    string const &defaultType = d_rules.sType();    // get the default type

                            // warn if the rule has no associated type: in
                            // that case it's peculiar that we need an
                            // explicit type here
    if (typeSpec.length() && !defaultType.length())
        noDefaultTypeWarning();

    string replacement = s_semanticValue;

    string const &type =    typeSpec.length() ? typeSpec : defaultType;

    if (type.length())      // use an explicit type if available
        replacement += "." + type;

    block.replace(dollar1, pos - dollar1 + 1, replacement);

    return true;            // this block uses $$
}

