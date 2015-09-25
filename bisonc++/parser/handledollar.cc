#include "parser.ih"

// See 'README.dollar' in this directory for a description of the actions
// involved at these alternatives.


bool Parser::handleDollar(Block &block, AtDollar const &atd, int nElements) 
{
    if (errIndexTooLarge(atd, nElements))
        return atd.returnValue();
    
    ostringstream os;
    string replacement;

    if (atd.returnValue())
        replacement = s_semanticValue;
    else
    {
        os << s_semanticValueStack << 
                "[" << indexToOffset(atd.nr(), nElements) << "]";
        replacement = os.str();
    }

    switch (d_semType)
    {
        case SINGLE:
            returnSingle(atd);
        break;

        case UNION:
            replacement += returnUnion(atd);
        break;

        case POLYMORPHIC:
            replacement += returnPolymorphic(atd);
        break;
    }
                                        // replace $$ by the semantic value
    block.replace(atd.pos(), atd.length(), replacement);

    return atd.returnValue();           // $$ is used
}




