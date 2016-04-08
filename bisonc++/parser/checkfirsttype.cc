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

    if 
    (
        d_options.defaultActions().value != Options::STD 
        &&
        d_semType == POLYMORPHIC
    ) 
    {
        defaultPolymorphicAction();
        return;
    }

    Production const &prod = d_rules.lastProduction();
    size_t nElements = prod.size();

    installDefaultAction(
        prod, 
        nElements > 0 ? svsElement(nElements, 1) : s_stype + "{}"s
    );
}





