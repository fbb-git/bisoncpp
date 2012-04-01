#include "parser.ih"

// pos points at the 2nd $ in '$<type>$'

bool Parser::dollarTypedDollar(size_t pos, Block &block) 
{
    size_t dollar1 = block.find_last_of("$", pos - 1);

                                // no first $ or no $<
    if (dollar1 == string::npos || block[dollar1 + 1] != '<')
        throw 1;

    string typeSpec;        // get the explicit type
    extractType(&typeSpec, dollar1 + 1, block);


    string replacement = s_semanticValue;

    switch (d_semType)
    {
        case SINGLE:
        break;

        case UNION:
            replacement += dollarTypedDollarUnion(typeSpec);
        break;

        case POLYMORPHIC:
            replacement += dollarTypedDollarPolymorphic(block, pos, typeSpec);
        break;
    }

    block.replace(dollar1, pos - dollar1 + 1, replacement);

    return true;            // this block uses $$
}
