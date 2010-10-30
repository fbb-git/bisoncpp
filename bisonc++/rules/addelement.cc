#include "rules.ih"

void Rules::addElement(Symbol *symbol)
{
    d_currentProduction->push_back(symbol);

// If the display of the new element is really requested (it isn't shown in
// bisonc++ 2.8.0) then pass yylineno from parser/handleproductionelement.cc
// and parser/nestedblock.cc to this function so the line can be 

//  imsg.setLineNr(lineNr);
//  imsg << "      $"  << d_currentProduction->size() << ": " << symbol << 
//                                                                      endl;
}
