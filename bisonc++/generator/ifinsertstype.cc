#include "generator.ih"

bool Generator::ifInsertStype() const
{
    return d_arg.option(0, "insert-stype");
}
