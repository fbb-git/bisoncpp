#include "parser.ih"

// We're at a $ character at position pos.
// The following can be expected here: $$, $$<type>, $i, $i<type>
//                                      ^   ^        ^   ^
// The following can be expected here: $$, $<type>$, $i, $<type>i
//                                      ^         ^  ^   ^
// (The ^ marking the `pos' location, searching proceeds from the end, see
// substuteBlock).  
//
// Depending on the $'s context the following happens:
//  - if there is a previous character:
//      - if it is a $, it is an explicit return of the rule's default 
//        semantic value (and done)
//      - if it is a >, then it must be an explicit return of a %union element
//        (and done)
//  - if the next character is a <, then an explicit value of the number
//    following the type-specification is used (and done).
//  - otherwise the next character must be a (possibly negative) number of a
//    rule element (and done)


bool Parser::handleDollar(size_t/*unsigned*/ pos, size_t/*unsigned*/ nElements) 
{
    if (pos)                    // there is a character before the $
    {
        if (d_block[pos - 1] == '$')    // it is '$', so '$$' was specified
            return defaultReturn(pos);

        if (d_block[pos - 1] == '>')    // it is '>', so expect '$<type>$' 
            return explicitReturn(pos);
    }

    // not one of the above alternatives

    if (d_block[pos + 1] == '<')        // it is '<', so expect $<type>i'
        return explicitElement(pos, nElements);
    
    return numberedElement(pos, nElements); // it must be $i
}
