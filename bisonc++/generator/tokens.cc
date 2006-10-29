#include "generator.ih"

void Generator::tokens(ostream &out) const
{
    Terminal::ConstVector tokens;
 
    for_each(d_rules.terminals().begin(), d_rules.terminals().end(), 
        Wrap1c<Terminal, Terminal::ConstVector>(selectSymbolic, &tokens)
    );
 
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








