#include "parser.ih"

// See 'README.dollar' in this directory for a description of the actions
// involved at these alternatives.


bool Parser::handleDollar(Block &block, AtDollar const &atd, int nElements) 
{
    switch (atd.action())
    {
        case AtDollar::RETURN_VALUE:
            returnValue(block, atd);
        return true;                        // true if $$ is used

//        case AtDollar::NUMBERED_ELEMENT:
//        return dollarIndex(pos, nElements, block); 
//
//        case AtDollar::TYPED_RETURN_VALUE:
//        return dollarTypedDollar(pos, block);
//
//        case AtDollar::TYPED_NUMBERED_ELEMENT:
//        return dollarTypedIndex(pos, nElements, block);
        
        default:
        return false;
    }
}
