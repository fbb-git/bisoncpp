#include "parser.ih"

Parser::Parser(Rules &rules)
:
    d_arg(Arg::instance()),
    d_scanner(d_arg[0]),
    d_rules(rules),
    d_debugFlag(d_arg.option(0, "debug")),
    d_errorVerbose(d_arg.option(0, "error-verbose")),
    d_generateBaseclass(!d_arg.option(0, "dont-rewrite-baseclass-header")),
    d_lines(false),
    d_lspNeeded(false),
    d_negativeDollarIndices(false),
    d_typeDirective(false),
    d_unionDeclared(false),
    d_requiredTokens(0),
    d_verboseName("(not requested)")
{
    string value;

    if (d_scanner.includeOnly())
    {
        lex();
        throw 0;
    }

    if (d_arg.option(&value, "required-tokens"))
        d_requiredTokens = A2x(value);

    d_scanner.set_debug(d_arg.option(0, "scanner-debug"));

    d_arg.option(&d_nameSpace, 'n');
    d_arg.option(&d_parsefunSource, 'p');
    d_arg.option(&d_genericFilename, 'f');

    predefine(Rules::errorTerminal());
    predefine(Rules::eofTerminal());

    if (d_arg.option(&d_preInclude, 'H'))
        addIncludeQuotes(&d_preInclude);
    
    if (d_arg.option(&d_implementationHeader, 'i'))
        addIncludeQuotes(&d_implementationHeader);
    
    if (d_arg.option(&d_scannerInclude, 's'))
        addIncludeQuotes(&d_scannerInclude);

    d_arg.option(&d_matchedTextFunction, "print");
}

