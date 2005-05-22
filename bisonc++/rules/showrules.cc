#include "rules.ih"

void Rules::showRules() const
{
    msg() << "Production Rules:" << info;

    for 
    (
        vector<Production *>::const_iterator prod = d_production.begin();
            prod !=  d_production.end();
                ++prod
    )
        msg() << *prod << info;

    msg() << info;
}
