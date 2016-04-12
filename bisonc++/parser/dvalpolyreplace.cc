#include "parser.ih"

bool Parser::dvalPolyReplace(bool midRule, Block &block, AtDollar const &atd, 
                                                        char const *suffix)
{
    string tag = warnAutoTag(midRule, atd);     // get the element's tag

    block.replace(atd.pos(), atd.length(), 
                s_semanticValue + 
                (
                    tag.empty() ? 
                        ""s 
                    : 
                        ".get<Tag__::" + tag + ">()"
                ) + suffix);

    return midRule || block.assignment();
}

