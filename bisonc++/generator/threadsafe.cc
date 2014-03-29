#include "generator.ih"

bool Generator::ifThreadSafe() const
{
    return d_arg.option(0, "thread-safe");
}
