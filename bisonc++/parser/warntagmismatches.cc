#include "parser.ih"

    // direct assignment is not used because the option variable may
    // already have been set using the --warn-tag-mismatches option,
    // which takes priority over the directive
void Parser::warnTagMismatches() const
{
    if (d_options.warnTagMismatches().triVal == Options::UNKNOWN)
        d_options.setWarnTagMismatches(Options::ON, d_scanner.filename(),
                                                    d_scanner.lineNr());
}
