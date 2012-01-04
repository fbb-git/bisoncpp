#include "generator.ih"

void Generator::tokens(ostream &out) const
{
    Terminal::ConstVector tokens;

    for (auto terminal: d_rules.terminals())
        selectSymbolic(terminal, tokens);

    key(out);
 
    if (!tokens.size())
    {
        out << "// No symbolic tokens were defined\n";
        return;
    }
 
    sort(tokens.begin(), tokens.end(), Terminal::compareValues);
 
    d_writer.useStream(out);
    d_writer.insert(tokens);
}



