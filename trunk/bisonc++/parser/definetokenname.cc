#include "parser.ih"

void Parser::defineTokenName(string *name, bool hasValue)
{
    defineTerminal(*name,   Symbol::SYMBOLIC_TERMINAL);

    if (hasValue)
    {
        lineMsg(wmsg) << "deprecated use of explicit value: `" << *name <<
                    ' ' << d_scanner.number() << '\'' << endl;
        d_rules.setLastTerminalValue(d_scanner.number());
    }
    delete name;
}
