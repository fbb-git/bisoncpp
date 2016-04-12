#include "parser.ih"

    // see parser.h about refByScanner for info why midRule
    // returns true.

bool Parser::dvalReplace(bool midRule, Block &block, AtDollar const &atd, 
                         char const *suffix)
{
    warnAutoTag(midRule, atd);
    
    block.replace(atd.pos(), atd.length(), s_semanticValue + suffix);

    return midRule || block.assignment();   // midrule assumes assignments,
                                            // to prevent warnings from
                                            // warnMissingSemval
}
