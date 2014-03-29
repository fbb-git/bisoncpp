#include "generator.ih"

void Generator::ifLtype(bool &accept) const
{
    accept = not d_options.ltype().empty();
}
