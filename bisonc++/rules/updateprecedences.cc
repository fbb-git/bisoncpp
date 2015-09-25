#include "rules.ih"

// The precedence of a production rule is defined either explicitly (using
// %prec) or it is defined as the priority setting of the rule's first
// terminal token. If none is found the production rule has a default
// priority. 

void Rules::updatePrecedences()
{   
    for (auto production: d_production)
        updatePrecedence(production, d_terminal);
}
