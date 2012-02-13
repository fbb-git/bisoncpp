#include "options.ih"

void Options::showFilenames() const
{
    if (!d_arg.option(0, "show-filenames"))
        return;

    cout << 
        "\n"
        "SKELETONS AND FILENAMES:\n"
        "  Base class skeleton:\n"
        "\t`" << d_baseClassSkeleton << "'\n"
        "  Class skeleton:\n"
        "\t`" << d_classSkeleton << "'\n"
        "  Implementation header skeleton:\n"
        "\t`" << d_implementationSkeleton << "'\n"
        "  Parser implementation skeleton:\n"
        "\t`" << d_parsefunSkeleton << "'\n"
        "\n"
        "  Base class header:           `" << d_baseClassHeader << "'\n"
        "  Class header:                `" << d_classHeader << "'\n"
        "  Implementation header:       `" << d_implementationHeader << "'\n"
        "  Parser Implementation:       `" << d_parsefunSource << "'\n"
        "  Verbose grammar description: `" << d_verboseName << "'\n"
        "\n";
}




