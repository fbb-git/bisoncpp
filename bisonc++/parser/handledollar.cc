#include "parser.ih"

// See 'README.dollar' in this directory for a description of the actions
// involved at these alternatives.


bool Parser::handleDollar(Block &block, AtDollar const &atd, int nElements) 
{
    string replacement = s_semanticValue;           // use the semantic value
                                                    // data member
    switch (d_semType)
    {
        case SINGLE:
            returnSingle(atd);
        break;

        case UNION:
            replacement += returnUnion(atd);
        break;

        case POLYMORPHIC:
            replacement += returnPolymorphic(atd);
        break;
    }
                                        // replace $$ by the semantic value
    block.replace(atd.pos(), atd.length(), replacement);

    return atd.nr() == numeric_limits<int>::max();  // $$ is used
}




