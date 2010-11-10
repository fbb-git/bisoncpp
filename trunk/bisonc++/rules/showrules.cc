#include "rules.ih"

void Rules::showRules() const
{
    if (!imsg.isActive())
        return;

    imsg << "\n"
            "Production Rules\n"
            "(rule precedences determined from %prec or 1st terminal between "
                                                         "parentheses):\n";
    copy(d_production.begin(), d_production.end(), 
         ostream_iterator<Production const *>(imsg, "\n"));

    imsg << endl;
}
