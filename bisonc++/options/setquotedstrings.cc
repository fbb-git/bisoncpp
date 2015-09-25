#include "options.ih"

void Options::setQuotedStrings()
{
    d_arg.option(&d_preInclude, 'H');
    addIncludeQuotes(d_preInclude);

    d_arg.option(&d_scannerInclude, 's');
    addIncludeQuotes(d_scannerInclude);
}
