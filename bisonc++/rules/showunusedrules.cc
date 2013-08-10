#include "rules.ih"

void Rules::showUnusedRules() const
{
    Terminal::inserter(&Terminal::plainName);

    for_each(d_production.begin(), d_production.end(), &Production::unused);

    if (Production::notUsed())
        imsg << endl;
}
