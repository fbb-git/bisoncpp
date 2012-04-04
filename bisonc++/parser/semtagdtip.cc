//#include "parser.ih"
//
//    // A specific type was provided (as in $<TYPE>$)
//
//Parser::SemTag Parser::semTagDTIP(
//                    size_t nElements, std::string const &autoTag, int idx, 
//                    std::string const &tagName) const
//{
//    if (idx > static_cast<int>(nElements))
//        return UNTYPED;
//        
//    if (autoTag.empty())
//    {
//        warnNoAuto("type");
//        return semTagDTaux(tagName);
//    }
//
//    if (autoTag == "STYPE__")
//        return semTagDTaux(tagName);
//
//    if (d_polymorphic.find(tagName) == d_polymorphic.end())
//    {
//        noSemanticTag(tagName);
//        return UNTYPED;
//    }
//
//    return tagName == autoTag ? TYPED : DELTATYPED;
//}
//
//
