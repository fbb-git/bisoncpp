#include "parser.ih"

RuleValue Parser::setDataType()
{
    string type = d_scanner.YYText();
    return 
        type == "char"  ? RuleValue(RuleValue::CHAR)    :
        type == "int"   ? RuleValue(RuleValue::INT)     :
           /* double */   RuleValue(RuleValue::DOUBLE);
}
