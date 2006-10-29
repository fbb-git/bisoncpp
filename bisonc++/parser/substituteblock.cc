#include "parser.ih"

// Stack_offset is the number of values in the current alternative so far, so
// it is d_elements.size(). It indicates where to find $0 with respect to the 
// top of the (?) stack. 

void Parser::substituteBlock(size_t nElements)
try
{
        // Look repeatedly for special characters. Do this from the end of the
        // block-text to the beginning. If a special character is found,
        //  - ignore it if it is in an ignorable range
        //  - if not in an ignorable range, replace it by its meaning

    d_skipRbegin = d_block.skipRbegin();
    d_skipRend = d_block.skipRend();

    size_t end = string::npos;
    size_t begin;

    bool explicitReturn = false;            // block return type as yet
                                            // unknown

                                            // find the last special char
                                            // skip it if it's in a
                                            // range that can be ignored
    while                                   // (i.e., in a d_scanner.skip()
    (                                       // range)
        (begin = skipIgnore(d_block.find_last_of("$@", end))) 
        !=
        string::npos
    )
    {
        switch (d_block[begin])
        {
            case '$':                       // $... refers to semantic value
                                            // stack element
                explicitReturn |= handleDollar(begin, nElements);
            break;

            case '@':                       // @... refers to location stack
                handleAtSign(begin, nElements); 
            break;
        }
        end = begin;                        // next search starts at begin,
                                            // ($, @: now substituted)
    }
    if (!explicitReturn)
        checkBlocktype();
}
catch (int)
{
    lineMsg() << "rule `" << d_rules.name() << 
                        "': incomplete $-specification" << err;
}
