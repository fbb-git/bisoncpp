#include "parser.ih"

    // I've seen the begin of a rule. If not yet defined, do so
    // now, and prepare for productions.
void Parser::openRule(string *ruleNamePtr)
{
    NonTerminal *nt = requireNonTerminal(*ruleNamePtr);
                                                // rule must start with N

    if (nt)
    {                                           // quit if not
        if (not d_rules.newRule(nt, d_scanner.source(), d_scanner.lineno()))
        {
            Rules::FileInfo const &fileInfo = d_rules.fileInfo(nt);
    
            lineMsg() << "Extending rule `" << *ruleNamePtr << 
                        "', first defined in `" << fileInfo.first << 
                        "' (" << fileInfo.second << ")" << warning;
        }
        d_rules.addProduction();
    }
    delete ruleNamePtr;
}



