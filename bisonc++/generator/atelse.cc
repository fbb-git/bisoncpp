#include "generator.ih"

void Generator::atElse(bool &accept) const
{
    accept = not accept;
}
