#include "rules.hh"

void Rules::showUnusedTerminals() const
{
    Terminal::inserter(&Terminal::valueQuotedName);

    for_each(d_terminal.begin(), d_terminal.end(), &Terminal::unused);
}
