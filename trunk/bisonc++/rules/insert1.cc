#include "rules.ih"

Terminal *Rules::insert(Terminal *terminal, std::string const &literal)
{
    d_terminal.push_back(terminal);

    if (terminal->name() != literal)
        d_terminal.back()->setLiteral(literal);

    return d_terminal.back();
}
