#include "parser.ih"

Parser::Parser(Rules &rules)
:
    d_arg(Arg::instance()),
    d_options(Options::instance()),
    d_scanner(d_arg[0]),
    d_matched(d_scanner.matched()),
    d_rules(rules)
{
    d_options.setMatched(d_matched);

    int debugMode = d_arg.option(0, "own-debug") ? ON : OFF;
    if (d_arg.option('a'))
        debugMode |= ACTIONCASES;
    setDebug(debugMode);

    d_scanner.setDebug(d_arg.option(0, "scanner-debug"));

    predefine(Rules::errorTerminal());
    predefine(Rules::eofTerminal());
}

