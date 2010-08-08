#include "rules.ih"

void Rules::showRules() const
{
    if (!Msg::display())
        return;

    msg() << info;

    msgstream() << "Production Rules\n"
        "(rule precedences determined from %prec or 1st terminal between "
                                                         "parentheses):\n";
    copy(d_production.begin(), d_production.end(), 
         ostream_iterator<Production const *>(msgstream(), "\n"));

    msgstream() << info;

}
