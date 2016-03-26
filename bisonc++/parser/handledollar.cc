#include "parser.ih"

// See 'README.dollar' in this directory for a description of the actions
// involved at these alternatives.

    // $$               no deref, no members: OK
    // $-?NR 

    // ($$)             deref: requires TAG
    // ($NR) 

    // $$.              members: requires TAG
    // $$->
    // $NR. 
    // $NR->

    // ($<ID>-NR)       deref: TAG assumed correct
    // $<ID>-NR.        member: TAG assumed correct
    // $<ID>-NR->               TAG assumed correct

bool Parser::handleDollar(Block &block, AtDollar const &atd, int nElements) 
{
    if (errIndexTooLarge(atd, nElements))
        return atd.dollarDollar();

    ostringstream replacement;

    if (atd.dollarDollar())
        replacement << s_semanticValue;
    else
        replacement << s_semanticValueStack << 
                "[" << indexToOffset(atd.nr(), nElements) << "]";

    switch (d_semType)
    {
        case SINGLE:
            returnSingle(atd);
        break;

        case UNION:
            replacement << returnUnion(atd);
        break;

        case POLYMORPHIC:
            replacement << returnPolymorphic(atd);
        break;
    }
                                        // replace $$ by the semantic value
    block.replace(atd.pos(), atd.length(), replacement.str());

    return atd.dollarDollar();           // $$ is used
}




