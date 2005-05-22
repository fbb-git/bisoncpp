#include "parser.ih"

// We're at a $ character at position pos.
// The following can be expected here: $$, $$<type>, $i, $i<type>
//                                      ^   ^        ^   ^
// (The ^ marking the `pos' location). 

bool Parser::handleDollar(unsigned pos, unsigned nElements) 
{
    bool explicitReturn = pos && d_block[pos - 1] == '$';
    unsigned replaceSize = 1 + explicitReturn;

    string replacement;

    replaceSize += 
        explicitReturn ?
            blockReturn(&replacement, pos + 1)
        :
            blockElement(&replacement, pos + 1, nElements);

    d_block.replace(pos - explicitReturn, replaceSize, replacement);

    return explicitReturn;
}
