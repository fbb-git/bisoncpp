#include "parser.ih"

Parser::Parser(Rules &rules)
:
    d_arg(Arg::instance()),
    d_options(Options::instance()),
    d_scanner(d_arg[0]),
    d_matched(d_scanner.matched()),
    d_rules(rules),
    d_typeDirective(false),
    d_unionDeclared(false),
    d_negativeDollarIndices(false),
    d_lspNeeded(false)

//    d_debugFlag(d_arg.option(0, "debug")),
//    d_errorVerbose(d_arg.option(0, "error-verbose")),
//    d_generateBaseclass(!d_arg.option(0, "dont-rewrite-baseclass-header")),
//    d_lines(false),
//    d_requiredTokens(0),
{
    string value;

    if (d_scanner.includeOnly())
    {
        lex();
        throw 0;
    }

    d_scanner.setDebug(d_arg.option(0, "scanner-debug"));

    predefine(Rules::errorTerminal());
    predefine(Rules::eofTerminal());
}

