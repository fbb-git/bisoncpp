#include "parser.ih"

// pos points to $ in what must be $i

bool Parser::dollarIndex(size_t pos, int nElements, Block &block) 
{
    int idx;                // extract the index, determine its length
    size_t length  = extractIndex(&idx, pos + 1);
    string const &idxType = d_rules.sType(idx);
    size_t ruleElements = nComponents(nElements);


    ostringstream os;
    os << s_semanticValueStack << "[" << indexToOffset(idx, nElements) << 
                                  "]";
    string replacement = os.str();


    switch (d_semType)
    {
        case SINGLE:
            if (not d_negativeDollarIndices && idx <= 0)
                wmsg << &d_rules.lastProduction() << ": "
                        "non-positive $" << idx << " used" << endl;
        break;

        case UNION:
            replacement += dollarIndexUnion(idx, idxType, ruleElements);
        break;

        case POLYMORPHIC:
            replacement += dollarIndexPolymorphic(block, pos, typeSpec);
        break;
    }

    block.replace(pos, length + 1, replacement);    // + 1 for the $

    return false;           // this is not a $$ variant.
}


//    if (idx > static_cast<int>(ruleElements)) // $i refers beyond this rule
//        emsg << "In production rule \n"<< 
//                "\t`" << &d_rules.lastProduction() << " '\n"
//                "\t$" << idx << " used, but there are only " << 
//                ruleElements << " elements" << endl;
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
//        else if (!idxType.length())     // or $i without type association
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
//    if (idxType.length())
//    {
//        if (d_semType == UNION)                     // no %polymorphic type
//            replacement += "." + idxType;
//        else if (replaceDollar(block, pos + length, idxType)) // %polymorphic
//        {
//            if (d_polymorphic.find(idxType) != d_polymorphic.end())
//                replacement += ".get<" + idxType + ">()";
//            else
//                emsg << "no such polymorphic semantic value identifier `" <<
//                        idxType << '\'';
//        }
//    }

