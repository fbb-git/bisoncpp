#include "Parser.ih"

Parser::FunctionPair Parser::s_funTab[] =
{
    FunctionPair("sin",  sin),
    FunctionPair("cos",  cos),
    FunctionPair("atan", atan),
    FunctionPair("ln",   log),
    FunctionPair("exp",  exp),
    FunctionPair("sqrt", sqrt),
};

unordered_map<string, double (*)(double)> Parser::s_functions
(
    Parser::s_funTab, 
    Parser::s_funTab + sizeof(Parser::s_funTab) / sizeof(Parser::FunctionPair)
);



