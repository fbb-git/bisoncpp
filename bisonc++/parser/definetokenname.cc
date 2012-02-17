#include "parser.ih"

void Parser::defineTokenName(string const &name, bool hasValue)
{
    defineTerminal(name, Symbol::SYMBOLIC_TERMINAL);

    if (hasValue)
    {
        wmsg << "deprecated use of explicit value: `" << name <<
                    ' ' << d_scanner.number() << '\'' << endl;
        d_rules.setLastTerminalValue(d_scanner.number());
    }
}
