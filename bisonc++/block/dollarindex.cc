//#include "block.ih"
//
//    // $-?NR, $NR. $NR-> ($NR)
//
//#include <iostream>
//
//void Block::dollarIndex(size_t lineNr, string const &text)
//{
//    int nrIdx = text[0] == '(' || text[1] == '-' ? 2 : 1;
//
//    d_atDollar.push_back(
//        AtDollar(text[0] == '(' ? AtDollar::DEREF :AtDollar::DOLLAR, 
//                 length(), lineNr, text, stol(text.substr(nrIdx)))
//    );
//
//    append(text);
//}
