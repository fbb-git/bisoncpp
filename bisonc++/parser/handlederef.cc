#include "parser.ih"

// See 'README.dollar' in this directory for a description of the actions
// involved at these alternatives.

    // ($<ID>-NR)  ($$) ($NR)


//void Parser::handleDeref(Block &block, AtDollar const &atd) 
//{
//    if (d_semType != POLYMORPHIC)
//    {
//        emsg << '`' << &d_rules.lastProduction() << 
//                "':  $$(...) requires %polymorphic" << endl;
//        return;
//    }
//
//cerr << "handlederef: " << atd.text() << '\n';
//
//    if (atd.nr() > 0)               // $<ID>-nr is unconditionally accepted 
//    {
//
//    string replacement = s_semanticValue;
//
//    replacement += 
//        stype == "STYPE__"?
//            " = ("s
//        :
//            ".assign<Tag__::" + d_rules.sType() + ">(";
//
//                                        // replace $$ by the semantic value
//    block.replace(atd.pos(), atd.length(), replacement);
//}




