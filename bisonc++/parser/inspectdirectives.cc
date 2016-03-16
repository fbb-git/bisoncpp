#include "parser.ih"

void Parser::inspectDirectives() const
{
    Options::OptInfo const *info = &d_options.constructorChecks();

    if (d_semType == POLYMORPHIC)       // the following options/directives
    {
        if (info->triVal == Options::UNKNOWN)
            d_options.setConstructorChecks(Options::ON, "", 0);

        return;                         // are OK for polymorphic sem. values
    }

    cerr << "value is " << info->triVal << '\n';

    static char const trailer[] = "ignored (requires %polymorphic)";

    switch (info->triVal)
    {
        case Options::UNKNOWN:
        break;

        case Options::OFF:
            wmsg << "--no-constructor-checks\n"
                    "    option " << trailer << endl;
        break;

        case Options::ON:
            wmsg << ": %no-constructor-checks (" << info->filename <<
                                            ": " << info->lineNr << ")\n"
                    "    directive " << trailer << endl;
            d_options.setConstructorChecks(Options::UNKNOWN, "", 0);
        break;
    }

    info = &d_options.warnTagMismatches();

    if (info->triVal == Options::ON)
    {
        if (info->lineNr != 0)
            wmsg << "--warn-tag-mismatches ";
        else 
            wmsg << info->filename << ": " << info->lineNr << 
                    ": %warn-tag-mismatches ";
        wmsg << " ignored (requires %polymorphic)" << endl;
        d_options.setWarnTagMismatches(Options::OFF, "", 0);
    }

}
