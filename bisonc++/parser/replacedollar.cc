// #include "parser.ih"
// 
// bool Parser::replaceDollar(Block const &block, size_t pos, 
//                            string const &defaultType) 
// {
//     bool defaultSTYPE = defaultType == "STYPE__";
// 
//     if (defaultSTYPE)               // no replacement for mere STYPE__ sem.
//     {                               // values
//         noDefaultTypeWarning();
//         return false;               
//     }
// 
//     if (block.length() == pos + 1)  // replacement if nothing trails the $:
//         return true;                // no member is called, so call .get<id>()
// 
//                                     // locate the next non-blank char
//     pos = block.find_first_not_of(" \t\n", pos + 1);
// 
//                                     // call .get<id>() if there isn't one or
//                                     // if the non-blank char isn't a '.'
//     return pos == string::npos || block[pos] != '.';
// }
