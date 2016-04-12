#include "parser.ih"

    // $$(
bool Parser::dvalPolyPar(int nElements, Block &block, AtDollar const &atd)
{
    string tag = warnAutoTag(nElements < 0, atd);

    block.replace(atd.pos(), atd.length(), 
                s_semanticValue + 
                (
                    tag.empty() ? 
                        "("s                                // )
                    : 
                        ".assign<Tag__::" + tag + ">("      // )
                )
            );

    return true;
}
