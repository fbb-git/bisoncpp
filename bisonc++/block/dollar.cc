//#include "block.ih"
//
//void Block::dollar(size_t lineNr, string const &text)
//{
//    d_atDollar.push_back(
//        AtDollar(
//            text[0] == '@' ?    AtDollar::AT  :
//            text[0] == '$' ?    AtDollar::DOLLAR : 
//                                AtDollar::DEREF, 
//            length(), lineNr, 
//            text, numeric_limits<int>::max()
//        )
//    );
//    d_usedDollarDollar |= text[0] == '$';
//
//    append(text);
//}
