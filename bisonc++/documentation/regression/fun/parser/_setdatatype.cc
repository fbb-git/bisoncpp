#include "parser.ih"

RuleValue Parser::setDataType()
{
    string type = d_scanner.matched();
    return 
        type == "char"  ? RuleValue(RuleValue::CHAR)    :
        type == "int"   ? RuleValue(RuleValue::INT)     :
           /* double */   RuleValue(RuleValue::DOUBLE);
}
