#include "parser.ih"

    // direct assignment is not used because the option may already 
    // have been set using the --no-constructor-checks option,
    // which takes priority over the directive
void Parser::noConstructorChecks() const
{
    d_options.setConstructorChecks(Options::OFF, d_scanner.filename(),
                    d_arg.option(0, "no-constructor-checks") ?
                        0
                    :
                        d_scanner.lineNr()
    );
}
