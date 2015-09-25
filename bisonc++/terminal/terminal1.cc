#include "terminal.ih"

#include <iostream>

Terminal::Terminal(string const &name, Type type, 
                   size_t value, Association association, 
                   std::string const &stype)
:
    Symbol(name, type, stype),
    d_value(value == DEFAULT ? s_value++ : value),
    d_association(association),
    d_precedence(s_precedence),
    d_literal(name),
    d_readableLiteral(name),
    d_firstSet(this)
{
    if (name.find("'\\x") == 0)
    {
        int charRepresentation;
        istringstream convert(name.substr(3));
        convert >> hex >> charRepresentation;
        if (isprint(charRepresentation))
        {
            d_readableLiteral = "'";
            d_readableLiteral.append(1, static_cast<char>(charRepresentation));
            d_readableLiteral += "'";
        }
    }

// If the terminal definition is really requested (it isn't shown in bisonc++
// 2.8.0) then pass yylineno from parser/useterminal.cc and
// parser/defineterminal.cc to this function so the line can be shown.
//
//  imsg.setLineNr(lineNr);
//  imsg << "Defining terminal " << d_readableLiteral << ": pri = " << 
//                                                      d_precedence << endl;
    if (d_value > s_maxValue)
        s_maxValue = d_value;
}

