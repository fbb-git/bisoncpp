#include "parser.ih"

void Parser::defineTokenName(string *name, bool hasValue)
{
    defineTerminal(*name,   Symbol::SYMBOLIC_TERMINAL);

    if (hasValue)
    {
        lineMsg() << "deprecated use of explicit value: `" << *name <<
                    ' ' << d_scanner.number() << "'" << warning;
        d_rules.setLastTerminalValue(d_scanner.number());
    }
    delete name;
}
