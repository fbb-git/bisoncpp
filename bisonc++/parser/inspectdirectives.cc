#include "parser.ih"

void Parser::inspectDirectives() const
{
    Options::OptInfo const *info = &d_options.constructorChecks();
    
    if (d_semType == POLYMORPHIC)       // the following options/directives
    {
        if (info->triVal == Options::UNKNOWN)
            d_options.setConstructorChecks(Options::ON);

        return;                         // are OK for polymorphic sem. values
    }

    if (info->triVal == Options::OFF)
    {
        if (info->lineNr != 0)
            wmsg << "--no-constructor-checks ";
        else 
            wmsg << info->filename << ": " << info->lineNr << 
                    ": %no-constructor-checks ";
        wmsg << " ignored (requires %polymorphic)" << endl;
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
        d_options.setWarnTagMismatches(Options::OFF);
    }

}
