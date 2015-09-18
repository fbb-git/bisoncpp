#include "generator.hh"

void Generator::atElse(bool &accept) const
{
    accept = not accept;
}
