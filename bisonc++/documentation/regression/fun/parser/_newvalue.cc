#include "parser.ih"

RuleValue Parser::newValue(int typeToken)
{
    switch (typeToken)
    {
        case CHAR:
        return RuleValue(
                    static_cast<char>(A2x(d_scanner.matched().substr(1))));

        case INT:
        return RuleValue(static_cast<int>(A2x(d_scanner.matched())));

        case IDENT:
        return identValue();
    }

    return RuleValue(static_cast<double>(A2x(d_scanner.matched())));
}
