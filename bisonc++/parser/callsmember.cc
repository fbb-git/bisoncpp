//#include "parser.ih"
//
//bool Parser::callsMember(char const *label, AtDollar const &atd,
//                     bool (Parser::*testFun)(std::string const &) const) const
//{
//    if (not atd.callsMember())
//        return false;
//
//    switch (semTag(label, atd, testFun))
//    {
//        case NONE:
//        break;
//
//        case AUTO:
//            warnAutoIgnored(label, atd);
//        break;
//
//        case EXPLICIT:
//        return false;
//    }
//        
//    return true;
//}

