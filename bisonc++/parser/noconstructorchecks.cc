#include "parser.ih"

    // direct assignment is not used because the option variable may
    // already have been set using the --no-constructor-checks option,
    // which takes priority over the directive
void Parser::noConstructorChecks() const
{
    if (d_options.constructorChecks().triVal == Options::UNKNOWN)
        d_options.setConstructorChecks(Options::OFF);
}
