#include "parser.ih"

//PTag *Parser::handleProductionElements(PTag *first, PTag *second)
//{
//    if (!first)         // the first PTag was a %prec specification
//        return second;  
//    if (!second)        // the second PTag was a %prec specification:
//        return first;   // postpone handling of first
//
//        // maybe also when currentRule == 0 ? See addProduction
//    if (!d_rules.hasRules())    // may happen if the first rule could not be
//        return (first);         // defined because of token/rulename clash
//
//
//    switch (first->tag)
//    {
//        case PTag::TERMINAL:
//            d_rules.addElement(first->terminal);
//        break;
//        case PTag::SYMBOL:
//            d_rules.addElement(first->symbol);
//        break;
//        case PTag::BLOCK:
//            nestedBlock(first->block);
//        break;
//        case PTag::NONE:    // can't occur, but used to keep the 
//        break;              // compiler from generating a warning
//    }
//
//    delete first;
//    return second;
//}
//
//
//
