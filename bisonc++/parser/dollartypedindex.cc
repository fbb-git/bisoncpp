#include "parser.ih"

// pos points to $ in what must be $<type>i

bool Parser::dollarTypedIndex(size_t pos, int nElements, Block &block) 
{
    string explicitType;        // extract the explicit type
    size_t length = 1 + extractType(&explicitType, pos + 1, block);


    int idx;                // extract the index, determine its length
    length  += extractIndex(&idx, pos + length);
    string const &idxType = d_rules.sType(idx); // get the idx'th default type
    size_t ruleElements = nComponents(nElements);


    ostringstream os;
    os << s_semanticValueStack << "[" << indexToOffset(idx, nElements) << 
                                  "]";
    string replacement = os.str();


    switch (d_semType)
    {
        case SINGLE:
            emsg << "No %union/%polymorphic declaration: can't resolve $<" << 
                    explicitType << ">" << idx << " for element $" << idx << 
                    " in `" << d_rules.name()  << endl;
        return false;                           // false: no $$ variant

        case UNION:
            replacement += dollarTypedIndexUnion(idx, idxType, ruleElements, 
                                                 explicitType);
        break;

        case POLYMORPHIC:
            replacement += dollarTypedDollarPolymorphic(block, pos, typeSpec);
        break;
    }

    block.replace(pos, length, replacement);

    return false;           // this is not a $$ variant.
}


