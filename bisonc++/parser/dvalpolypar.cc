#include "parser.ih"

    // $$(
bool Parser::dvalPolyPar(int nElements, Block &block, AtDollar const &atd)
{
    string tag = productionTag(atd.nr());        // get the element's tag

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
