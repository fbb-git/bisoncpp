#include "rules.ih"

bool Rules::newRule(NonTerminal *np, string const &source, size_t line)
{
    msg() << info;

    lineMsg() << "Adding production rule for `" << np->name() << "'" << info;

    if (!d_startRule.length())
        d_startRule = np->name();

    d_currentRule = np;

    NFileInfoMap::iterator nfIter = d_location.find(np);
    if (nfIter != d_location.end())
        return false;                   // extending an existing rulename

    d_location[np] = FileInfo(source, line);
    return true;
}
