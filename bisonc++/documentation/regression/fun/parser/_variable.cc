// #include "parser.hh"
// 
// RuleValue Parser::variable()
// {
//     // symtab stores the indices of the values of the variables in the 
//     // d_value vector. A new variable will not have an index, so then
//     // 0 is returned. In that case, the variable's value will be stored 
//     // at the end of the vector, and the variable's index in d_symtab
//     // is updated accordingly.
// 
//     unsigned idx = d_symtab[d_lastIdent];
// 
//     if (idx == 0)               // new identifier
//     {
//         d_symtab[d_lastIdent] = idx = d_value.size();
//         d_value.push_back(0);
//     }
// 
//     return RuleValue(idx, RuleValue::A_VARIABLE);
// }
