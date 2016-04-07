#include "parser.ih"

void Parser::blkNopW(string const &ruleType, Production const &prod)
{
    wmsg << '`' << &prod << 
            "': no default action block was installed" << endl;
}
