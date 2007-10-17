#include "parser.ih"

namespace{

    typedef Parser::FunctionMap     FunMap;
    typedef RuleValue::Function     Function;

FunMap::value_type funArray[] = 
{
    FunMap::value_type("abs",   
                            Function(static_cast<double (*)(double)>(abs))),

    FunMap::value_type("sqrt",  Function(&sqrt)),

    FunMap::value_type("exp",   Function(&exp)),
    FunMap::value_type("log",   Function(&log)),
    FunMap::value_type("ln",    Function(&log)),
    FunMap::value_type("log10", Function(&log10)),

    FunMap::value_type("sin", Function(&sin, Function::RAD_IN_DOUBLE_OUT)),
    FunMap::value_type("cos", Function(&cos, Function::RAD_IN_DOUBLE_OUT)),
    FunMap::value_type("tan", Function(&tan, Function::RAD_IN_DOUBLE_OUT)),

    FunMap::value_type("asin", Function(&asin, Function::DOUBLE_IN_RAD_OUT)),
    FunMap::value_type("acos", Function(&acos, Function::DOUBLE_IN_RAD_OUT)),
    FunMap::value_type("atan", Function(&atan, Function::DOUBLE_IN_RAD_OUT)),

    FunMap::value_type("pow", Function(&pow)),
};

unsigned const sizeofFunctionArray = sizeof(funArray) / 
                                            sizeof(FunMap::value_type);

typedef Parser::DoubleMap::value_type DoubleValue;

DoubleValue doubleArray[] = 
{
    DoubleValue("e", M_El),
    DoubleValue("E", M_El),
    DoubleValue("pi", M_PI),
    DoubleValue("PI", M_PI),
};

unsigned const sizeofDoubleArray = sizeof(doubleArray) / 
                                            sizeof(DoubleValue);
};


Parser::FunctionMap 
    Parser::s_functions(
        funArray, 
        funArray + sizeofFunctionArray
    );

Parser::DoubleMap
    Parser::s_doubles(
        doubleArray, 
        doubleArray + sizeofDoubleArray
    );

bool A2x::s_lastFail = false;
