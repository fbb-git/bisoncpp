#include "options.ih"

void Options::setParsingOptions()
{
    string value;

    if (d_arg.option(&value, 'd'))
        setDefaultAction(value, "", 0);

    if (d_arg.option(&value, "tag-mismatches"))
        setTagMismatches(value, "", 0);
}
