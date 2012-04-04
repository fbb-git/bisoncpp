//#include "parser.ih"
//
//Parser::SemTag Parser::semTagDTIU(size_t nElements, 
//                                  std::string const &autoField,
//                              int idx, std::string const &unionField) const
//{
//    if (idx > static_cast<int>(nElements))
//        return UNTYPED;
//        
//    if (autoField.empty())
//        return unionField.length() ? DELTATYPED : UNTYPED;
//
//    if (autoField == unionField)        // auto type was requested
//        return TYPED;
//                                            // try to override the auto field
//    return unionField.empty() ? TYPED : DELTATYPED;
//}





