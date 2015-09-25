#include "options.ih"

bool Options::isFirstStypeDefinition() const
{
    if (d_stackDecl.empty())
        return true;

    emsg << "Only one of %polymorphic, %stype, or %union can be specified" << 
            endl;

    return false;
}
