#include "parser.ih"

    // the production for which this member is called has elements, 
    // but does not define an action block.
    // Now check if the production's FIRST element's stype is equal
    // to the rule's stype or whether the rule's stype is empty (default)
    
void Parser::checkFirstType() 
{
    // The default (STD) action is to add $$ = $1, unconditionally

    // stype and union types by default use the $$ = $1 option
    // polymorphic types check the semantic value type of the first
    // production element 

    Production const &prod = d_rules.lastProduction();

    Options::Value actionType = d_options.defaultActions().value;

    if (actionType == Options::OFF)
        return;

    size_t nElements = prod.size();

    if (nElements == 0)
        return;

    if (actionType != Options::STD && d_semType == POLYMORPHIC) 
        defaultPolymorphicAction(prod);
    else
        installDefaultAction(prod, svsElement(nElements, 1) );
}





