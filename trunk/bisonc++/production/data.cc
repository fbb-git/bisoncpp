#include "production.ih"

size_t Production::s_nr;
bool Production::s_unused;

Production const *Production::s_startProduction;

std::ostream &(Production::*Production::s_insert[])(std::ostream &out) const =
{
    &Production::standard,
    &Production::standard,
    &Production::standard,
    &Production::standard,
};
