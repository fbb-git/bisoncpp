//#include "parser.ih"
//
//void Parser::warnAutoIgnored(char const *typeOrField, 
//                             AtDollar const &atd) const
//{
//    if (atd.nr() < 0)
//        negativeIndex(atd);
//    else
//    {
//        string const &autoType = d_rules.sType();
//
//        if (autoType.length())
//        {
//            wmsg.setLineNr(atd.lineNr());
//            wmsg << "rule " << &d_rules.lastProduction() << ":\n"
//                "\t\t`" << atd.text() <<
//                "' suppresses auto " << typeOrField << " `" << 
//                autoType << "' of `" << d_rules.name() << "'." << endl;
//        }
//    }
//}
