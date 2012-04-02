#include "parser.ih"

// pos points to $ in what must be $<type>i

bool Parser::dollarTypedIndex(size_t pos, int nElements, Block &block) 
{
    string explicitType;        // extract the explicit type
    size_t length = 1 + extractType(&explicitType, pos + 1, block);

    int idx;                // extract the index, determine its length
    length  += extractIndex(&idx, pos + length);
    string const &idxType = d_rules.sType(idx); // get the idx'th default type
    size_t nRuleElements = nComponents(nElements);

    if (not dollarIdx(idx, nRuleElements))
        return false;

    ostringstream os;
    os << s_semanticValueStack << "[" << indexToOffset(idx, nElements) << 
                                  "]";
    string replacement = os.str();


    switch (d_semType)
    {
        case SINGLE:
            noSTYPEtypeAssociations();
        return false;                           // false: no $$ variant

        case UNION:
            replacement += dollarTypedIndexUnion(nRuleElements, idx, idxType,
                                                 explicitType);
        break;

        case POLYMORPHIC:
            replacement += dollarTypedIndexPolymorphic(nRuleElements,
                                                idx, idxType, explicitType);
        break;
    }

    block.replace(pos, length, replacement);

    return false;           // this is not a $$ variant.
}


