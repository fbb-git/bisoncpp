#include "scanner.ih"

void Scanner::assignment()
{
    d_block.atDollar(lineNr(), "_" + d_matched.substr(0, length() - 1),
                    d_matched[1] == '$',   // saw '$$ =', so $$-assignment
                    true); // ref. by the scanner
    push(" =");
}
