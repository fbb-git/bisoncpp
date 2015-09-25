#include "parser.ih"

    // I've seen the begin of a rule. If not yet defined, do so
    // now, and prepare for productions.
void Parser::openRule(string const &ruleName)
{
    NonTerminal *nt = requireNonTerminal(ruleName);
                                                // rule must start with N

    if (nt)
    {                                           // quit if not
        if 
        (
            not d_rules.newRule(nt, 
                                d_scanner.filename(), d_scanner.lineNr())
        )
        {
            Rules::FileInfo const &fileInfo = d_rules.fileInfo(nt);
    
            wmsg << "Extending rule `" << ruleName << 
                    "', first defined in `" << fileInfo.first << 
                    "' (" << fileInfo.second << ")" << endl;
        }
        d_rules.addProduction(d_scanner.lineNr());
    }
}
