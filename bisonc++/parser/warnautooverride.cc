//#include "parser.ih"
//
//void Parser::warnAutoOverride(AtDollar const &atd) const
//{
//    if (atd.text() != d_rules.sType())
//        return;
//
//    wmsg.setLineNr(atd.lineNr());
//    wmsg << &d_rules.lastProduction() << ":\n"
//            "\t\t`" << atd.text() << "' overrides auto tag <" << 
//            d_rules.sType() << "> for `" << 
//            (
//                atd.nr() == numeric_limits<int>::max() ? 
//                    d_rules.name()
//                :
//                    d_rules.symbol(atd.nr())->name()
//            ) << "'." << endl;
//}
