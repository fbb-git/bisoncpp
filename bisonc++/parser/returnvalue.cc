//#include "parser.ih"
//
//void Parser::returnValue(AtDollar const &atd) 
//{
//    string replacement = s_semanticValue;           // use the semantic value
//                                                    // data member
//    switch (d_semType)
//    {
//        case SINGLE:
//        break;
//
//        case UNION:
//            replacement += returnUnion(atd);
//        break;
//
//        case POLYMORPHIC:
//            replacement += returnPolymorphic(block, pos);
//        break;
//    }
//                                        // replace $$ by the semantic value
//    block.replace(atd.pos(), atd.length(), replacement);
//}
//
//
//
