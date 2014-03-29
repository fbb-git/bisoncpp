#include "generator.ih"

bool Generator::ifLtype() const
{
    return not d_options.ltype().empty();
}
