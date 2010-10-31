#include "parser.ih"

void Parser::checkEmptyBlocktype() 
{
    string const &stype = d_rules.sType();

    if (stype.size())           // return type is required
        lineMsg(wmsg) << 
            "rule `" << d_rules.name() << 
            "': no return type for empty production rule of typed "
                                                    "nonterminal" << endl;
// Not shown in 2.8.0:
//    lineMsg(imsg) << "      <empty>" << endl;
}

