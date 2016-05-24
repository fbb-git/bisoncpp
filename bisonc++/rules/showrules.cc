#include "rules.ih"

void Rules::showRules() const
{
    if (!imsg.isActive())
        return;

    imsg << "\n"
        "Production Rules:\n"
        "   (precedences (shown between parentheses) were set by %prec;\n"
        "    are equal to the precedence of the rules' 1st terminal tokens;\n"
        "    or (if not shown) are equal to the default (max) precedence)\n";

    copy(d_production.begin(), d_production.end(), 
         ostream_iterator<Production const *>(imsg, "\n"));

    imsg << endl;
}
