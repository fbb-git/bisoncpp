#include "parser.ih"

// pos points to $ in what must be $i

bool Parser::dollarIndex(size_t pos, int nElements, Block &block) 
{
    int idx;                // extract the index, determine its length
    size_t length  = extractIndex(&idx, pos + 1);
    string const &elementType = d_rules.sType(idx);
    size_t nRuleElements = nComponents(nElements);

    if (not dollarIdx(idx, nRuleElements))
        return false;
        
    ostringstream os;
    os << s_semanticValueStack << "[" << indexToOffset(idx, nElements) << "]";
    string replacement = os.str();


    switch (d_semType)
    {
        case SINGLE:
        break;

        case UNION:
            replacement += dollarIndexUnion(block, pos + 1 + length, 
                                            nRuleElements, idx, elementType);
        break;

        case POLYMORPHIC:
            replacement += dollarIndexPolymorphic(block, pos + 1 + length, 
                                            nRuleElements, idx, elementType);
        break;
    }

    block.replace(pos, length + 1, replacement);    // + 1 for the $

    return false;           // this is not a $$ variant.
}


//    if (idx > static_cast<int>(nRuleElements)) // $i refers beyond this rule
//        emsg << "In production rule \n"<< 
//                "\t`" << &d_rules.lastProduction() << " '\n"
//                "\t$" << idx << " used, but there are only " << 
//                nRuleElements << " elements" << endl;
//    else if (d_semType != SINGLE)
//    {
//        if (idx <= 0)                   // type of the $i can't be determined
//        {                               // and indices <= 0 are not accepted
//            if (!d_negativeDollarIndices)
//                wmsg << "In production rule \n"<< 
//                            "\t`" << &d_rules.lastProduction() << " '\n"
//                            "\tcannot determine default type of $" << 
//                            idx << endl;
//        }
//        else if (!elementType.length())     // or $i without type association
//                wmsg << "In production rule \n"<< 
//                            "\t`" << &d_rules.lastProduction() << " '\n"
//                            "\t$" << idx << " (" << d_rules.symbol(idx) << 
//                            ") has no default type-association" << endl;
//    }
//    else if (!d_negativeDollarIndices && idx <= 0)
//        wmsg << "In production rule \n"<< 
//                    "\t`" << &d_rules.lastProduction() << " '\n"
//                    "\tnon-positive $" << idx << " used" << endl;
//
//    ostringstream os;
//    os << s_semanticValueStack << "[" << indexToOffset(idx, nElements) << "]";
//    string replacement = os.str();
//
//    if (elementType.length())
//    {
//        if (d_semType == UNION)                     // no %polymorphic type
//            replacement += "." + elementType;
//        else if (replaceDollar(block, pos + length, elementType)) // %polymorphic
//        {
//            if (d_polymorphic.find(elementType) != d_polymorphic.end())
//                replacement += ".get<" + elementType + ">()";
//            else
//                emsg << "no such polymorphic semantic value identifier `" <<
//                        elementType << '\'';
//        }
//    }

