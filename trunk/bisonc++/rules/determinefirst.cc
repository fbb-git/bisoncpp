#include "rules.ih"

void Rules::determineFirst()
{
    size_t lastCount = 0;     // counts the number of first-elements.

    while (true)
    {
        // Process all non-terminals (N). Handle all the production rules of
        // these non-terminals. For an empty production, the N gets <empty>.
        // For non-empty productions: add those element's first symbols, and
        // stop if an element has no empty production. If, at the end, the
        // final element has an empty production, add <empty> as well

        NonTerminal::resetCounter();

        for_each(d_nonTerminal.begin(), d_nonTerminal.end(),
                    &NonTerminal::setFirst);

        if (lastCount == NonTerminal::counter())
            break;

        lastCount = NonTerminal::counter();
    }
}
