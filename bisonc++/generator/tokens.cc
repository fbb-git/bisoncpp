#include "generator.ih"

void Generator::tokens(ostream &out) const
{
    vector<Terminal const *> symbolicTokens;

    SSContext context = {&symbolicTokens};

    for_each(d_rules.terminals().begin(), d_rules.terminals().end(), 
        Wrap1<Terminal const *, SSContext>
                  (&Generator::selectSymbolic, context));

    key(out);

    if (!symbolicTokens.size())
    {
        out << "// No symbolic tokens were defined\n";
        return;
    }

    sort(symbolicTokens.begin(), symbolicTokens.end(), 
        &Terminal::compareValues);

    out << "\n"
            "    // Symbolic tokens:\n"
            "    enum Tokens\n"
            "    {\n";

    unsigned lastValue = 0;
    for 
    (
        vector<Terminal const *>::const_iterator termIter = 
                                                        symbolicTokens.begin();
            termIter != symbolicTokens.end();
                ++termIter
    )
    {
        ++lastValue;
        Terminal const &term = **termIter;
        out <<  "        " << term.name();
        if (term.value() != lastValue)
        {
            lastValue = term.value();
            out << " = " << lastValue;
        }
        out << ",\n";
    }
    out <<  "    };\n"
           "\n";
}
