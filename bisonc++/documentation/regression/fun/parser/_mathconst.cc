#include "parser.ih"

RuleValue Parser::mathConst()
{
    string c = d_scanner.matched();

    return RuleValue(
            c == "E" ?  M_E : 
                        M_PI
                    );
}
