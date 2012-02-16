#include "parser.ih"

void Parser::defineTokenName(STYPE__ const &nm, STYPE__ const &hasValue)
{
    string const &name = nm->value<Type::STRING>();

    defineTerminal(name,   Symbol::SYMBOLIC_TERMINAL);

    if (hasValue->value<Type::BOOL>())
    {
        wmsg << "deprecated use of explicit value: `" << 
                    name->value<Type::STRING() <<
                    ' ' << d_scanner.number() << '\'' << endl;
        d_rules.setLastTerminalValue(d_scanner.number());
    }
}
