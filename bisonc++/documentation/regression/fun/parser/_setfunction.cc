//#include "parser.hh"
//
//RuleValue Parser::setFunction()
//{
//    stdFun1Map::iterator it;            // see if it's a unary function
//
//    it = s_stdfun1.find(d_lastIdent);
//
//    if (it != s_stdfun1.end())
//        return RuleValue(&*it);
//
//
//    stdFun2Map::iterator it2;           // see if it's a binary function
//
//    it2 = s_stdfun2.find(d_lastIdent);
//
//    if (it2 != s_stdfun2.end())
//        return RuleValue(&*it2);
//
//    return variable();                  // no, so it must be a variable
//}
