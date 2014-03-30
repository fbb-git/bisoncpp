#include "generator.ih"

void Generator::ifThreadSafe(bool &accept) const
{
    accept = d_arg.option(0, "thread-safe");
}
