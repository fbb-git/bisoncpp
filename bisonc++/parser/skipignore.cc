#include "parser.ih"

// skipRbegin points to [first, second), which is a half-open range of indices
// to be skipped. first belongs to the range, second is just beyond the range.
// The following possibilities exist:
//      ...second...
//         pos  (or larger):    return pos as the next element to be converted
//
//      ...first...second
//         pos (or larger, but smaller than second, which is implied)
//                              return pos - 1 (or npos) as the next element 
//                              to inspect
//      ........first       
//          pos                 increment rbegin if possible and redo the loop
//                              or return pos as the next element to inspect.

size_t/*unsigned*/ Parser::skipIgnore(size_t/*unsigned*/ pos) 
{
    while (d_skipRbegin != d_skipRend)
    {
        if (pos >= d_skipRbegin->second)    // beyond the skiprange:
            return pos;                     // convert this element

        if (pos >= d_skipRbegin->first)     // in the skip-range: search again
            return d_skipRbegin->first?     // before this range
                        d_skipRbegin->first - 1 
                    : 
                        string::npos; 
            
        ++d_skipRbegin;                     // use the previous range as pos
                                            // is already before the current
                                            // range, but it may be within the
                                            // previous range
    }
    return pos;
}
