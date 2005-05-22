#include "parser.ih"

    // I've seen the leading `RULE non-terminal. Parse its elements, and
    // return at the next RULE, unless it's the same as the current one.
void Parser::parseRule()
{
    d_scanner.cutColon();

    NonTerminal *np = useNonTerminal();

    if (!np)
        return;

    d_rules.addRule(np);
    newProduction();

    while (true)
    {
        switch (d_scanner.lex())
        {
            case Scanner::RULE:
                d_scanner.cutColon();
                if (d_scanner.text() != np->name())
                {
                    d_scanner.unget();      // re-read the rule's name
                    installAction();        // install the last block as the
                                            // the last production rule's 
                                            // action
                    return;
                }
            continue;

            case '|':
                showEmpty();
                newProduction();            // installs the last block as the
                                            // previous production's action
            continue;

            case Scanner::QUOTE:
                handleQuote();              // installs the last block as a
                                            // nested hidden rule
            continue;

            case Scanner::IDENTIFIER:
                handleIdent();              // installs the last block as a
                                            // nested hidden rule
            continue;

            case '{':                       // '}' (for emacs' block-matcher)
                handleBlock();              // installs an existing block as
                                            // a nested hidden rule and reads
                                            // another block
            continue;

            case Scanner::PREC:             // process a %prec statement.
                setPrecedence();
            continue;

            case ';':
                installAction();            // installs the last block as the
                                            // last production rule's action
            default:
                showEmpty();
            return;
        }
    }            
}


