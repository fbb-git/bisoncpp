#include "parser.ih"

RuleValue Parser::call(RuleValue const &function, RuleValue &argv)
{
    RuleValue ret;

    if (!d_error)
    {
        error(function.tag() != RuleValue::FUNCTION,
                "No such function");

        error(function.fun().arity() != argv.size(), 
                "Incorrect number of arguments");

        switch(argv.size())
        {
            case 1:
                ret = (function.fun().unary())(rvalue(argv[0]).asDouble());
            break;
    
            case 2:
                ret = (function.fun().binary())(rvalue(argv[0]).asDouble(), 
                                                rvalue(argv[1]).asDouble());
            break;
        }
    }
    return ret;
}



