#include "parser.ih"

RuleValue Parser::mathConst()
{
    string c = d_scanner.YYText();

    return RuleValue(
            c == "E" ?  M_E : 
                        M_PI
                    );
}
