#include "parser.ih"

// We're at a $ character at position pos.
// The following can be expected here: $$, $$<type>, $i, $i<type>
//                                      ^   ^        ^   ^
// The following can be expected here: $$, $<type>$, $i, $<type>i
//                                      ^         ^  ^   ^
// (The ^ marking the `pos' location, searching proceeds from the end, see
// substuteBlock).  
//
//  With %polymorphic: $$ and $i can be followed by . in which case a member
// is called, and $$ and $i is merely replaced by the indicated semantic value 
// variable. 
//
// Depending on the $'s context the following happens:
//  - if there is a previous character:
//      - if it is a $, we saw $$.
//          for %polymorphic: see below

if the next char = '(' then the semantic value
is initialized by its constructor.

//          otherwise: it is an explicit return of the rule's default 
//        semantic value (e,g, a union field) and done)
//      - if it is a >, then it must be an explicit return of a %union element
//          or %polymorphic semantic value type. In the latter case: see
//          below, and done.
//  - if the next character is a <, then an explicit value of the number
//    following the type-specification is used ($<spec>i). For %polymorphic:
//    see below  (and done).
//  - otherwise the next character must be a (possibly negative) number of a
//    rule element (and done)
// 
// With %polymorphic:
//     non-terminals may be tagged with a %polymorphic type tag, may be tagged
// with STYPE__ or may not be tagged at all. Tagging is done with 
// %type <tag identifier> (non-)terminal(s)
// 
// Here's what happens:
// 
// -------------------------------------------------------------------
//                             Used syntax:
//             -------------------------------------------------------
//                     rvalue               lvalue
//                 ----------------     --------------------
// Tag:            $$       $<tag>$     $$      $<tag>i   $i     $$., $i. 
// --------------------------------------------------------------------
// identifier      OK       OK          OK      OK        OK     OK
//                          warn-1              warn-1
// --------------------------------------------------------------------
// STYPE__         OK       OK          OK      OK        OK     OK
//                 warn-2               warn-2            warn-2        
// --------------------------------------------------------------------
// no tag          OK       OK          OK      OK        OK     OK
//                 warn-2   warn-3      warn-2  warn-3    warn-2 warn-3
// ====================================================================
// handling        default  explicit    default explicit  numb.  default
// function        Return   Return      Return  Return    elem.  Return
// --------------------------------------------------------------------
// 
// warn-1: warn if tag != identifier
// warn-2: warn that untagged STYPE__ is used
// warn-3: warn that sem. value is not tagged


bool Parser::handleDollar(size_t pos, int nElements, Block &block) 
{
    if (pos)                    // $$, $$. or $<type>$, pos at 2nd $
    {
        if (block[pos - 1] == '$')    // a '$': '$$' or '$$.' was specified
            return dollarDollar(pos, block);

        if (block[pos - 1] == '>')    // it is '>', so expect '$<type>$' 
            return dollarTypedDollar(pos, block);
    }

    // One dollar: $i, $i., $<type>i 

    return block[pos + 1] == '<' ?        // it is '<', so expect $<type>i'
                dollarTypedIndex(pos, nElements, block)
            : 
                dollarIndex(pos, nElements, block); // it must be $i or $i.
}


