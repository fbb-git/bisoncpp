#include "rules.ih"
    
bool Rules::newRule(NonTerminal *np, string const &source, size_t lineNr)
{
// If the terminal definition is really requested (it isn't shown in bisonc++
// 2.8.0) then pass yylineno from parser/openrule.cc and
// rules/augmentgrammar.cc to this function so the line can be shown.
//
//  imsg << endl;
//
//  imsg.setLineNr(lineNr);
//  imsg << "Adding production rule for `" << np->name() << "'" << endl;

    s_lastLineNr = lineNr;

    Production::storeFilename(source);

    if (!d_startRule.length())
        d_startRule = np->name();

    d_currentRule = np;

    NFileInfoMap::iterator nfIter = d_location.find(np);
    if (nfIter != d_location.end())
        return false;                   // extending an existing rulename

    d_location[np] = FileInfo(source, lineNr);
    return true;
}
