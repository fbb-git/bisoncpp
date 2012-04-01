#include "parser.ih"

// pos is the position of the second $ in '$$'
// this member always returns true

bool Parser::dollarDollar(size_t pos, Block &block) 
{
    string replacement = s_semanticValue;           // use the semantic value
                                                    // data member
    switch (d_semType)
    {
        case SINGLE:
        break;

        case UNION:
            replacement += dollarDollarUnion();
        break;

        case POLYMORPHIC:
            replacement += dollarDollarPolymorphic(block, pos);
        break;
    }

    block.replace(pos - 1, 2, replacement);         // replace $$ by semantic
                                                    // value

    return true;                                    // this block uses $$
}





