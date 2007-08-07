#include "rules.ih"

void Rules::showUnusedRules() const
{
    for_each(d_production.begin(), d_production.end(), &Production::unused);

    if (Production::notUsed())
        msg() << info;

    Msg::setWarning();
}
