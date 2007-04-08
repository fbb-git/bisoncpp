#include "parser.ih"

RuleValue Parser::identValue()
{
    DoubleMap::iterator doubleIt = s_doubles.find(d_scanner.YYText());

    if (doubleIt != s_doubles.end())
        return RuleValue(doubleIt->second);

    FunctionMap::iterator funIt = s_functions.find(d_scanner.YYText());

    if (funIt != s_functions.end())
        return RuleValue(funIt->second);

    unsigned symbolIdx = d_symtab[d_scanner.YYText()];

    if (symbolIdx == 0)                   // new identifier
    {
        d_symtab[d_scanner.YYText()] = symbolIdx = d_value.size();
        d_value.push_back(0);
    }

    return RuleValue(symbolIdx);
}

