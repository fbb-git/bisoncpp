#include "parser.ih"

    // direct assignment is not used because the option may already 
    // have been set using the --warn-tag-mismatches option,
    // which takes priority over the directive
void Parser::warnTagMismatches() const
{
    d_options.setWarnTagMismatches(Options::ON, d_scanner.filename(),
                            d_arg.option(0, "warn-tag-mismatches") ?
                                0
                            :
                                d_scanner.lineNr()
    );
}
