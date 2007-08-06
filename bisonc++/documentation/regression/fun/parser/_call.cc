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
            {
                double value = rvalue(argv[0]).asDouble();
                if 
                (
                    function.fun().type() ==
                    RuleValue::Function::RAD_IN_DOUBLE_OUT
                )
                    value = radians(value);

                value = (function.fun().unary())(value);

                if 
                (
                    function.fun().type() ==
                    RuleValue::Function::DOUBLE_IN_RAD_OUT
                )
                    value = angle(value);

                ret = value;
            }
            break;
    
            case 2:
                ret = (function.fun().binary())(rvalue(argv[0]).asDouble(), 
                                                rvalue(argv[1]).asDouble());
            break;
        }
    }
    return ret;
}



