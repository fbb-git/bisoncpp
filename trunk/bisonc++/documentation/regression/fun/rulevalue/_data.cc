#include "_rulevalue.ih"

char const *RuleValue::s_tagName[] =
{
    "error",                      // something failed.
    "char",
    "int",
    "double",
    "variable",
    "function",
    "argsector",
};
