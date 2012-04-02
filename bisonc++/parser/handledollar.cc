#include "parser.ih"

// We're at a $ character at position pos.
// The following can be encountered here: $$, $$., $<type>$, $i, $i., $<type>i
//                                         ^   ^          ^  ^   ^    ^
// (The ^ marking the `pos' location, searching proceeds from the end, see
// substuteBlock).  
//
// See 'README.dollar' in this directory for a description of the actions
// involved at these alternatives.


bool Parser::handleDollar(size_t pos, int nElements, Block &block) 
{
    cerr << "handleDollar " << pos << ", #elems: " << nElements << 
            ", block:\n" << block << endl;

    if (pos > 0)            // handle $$, $$. and $<type>$     (pos at 2nd $)
    {
        switch (block[pos - 1])
        {
            case '$':                   // '$$' or '$$.' was specified
            return dollarDollar(pos, block);

            case '>':                   // '$<type>$' is expected
            return dollarTypedDollar(pos, block);
        }
    }

    // One dollar: $i, $i., $<type>i 
    return 
        block[pos + 1] == '<' ?         // '$<type>i' is expected
            dollarTypedIndex(pos, nElements, block)
        :                               // '$i' or '$i.' is expected
            dollarIndex(pos, nElements, block); 
}


