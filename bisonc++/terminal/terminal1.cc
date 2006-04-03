#include "terminal.ih"

#include <iostream>

Terminal::Terminal(string const &name, Type type, Status status, 
                   unsigned value, Association association, 
                   std::string const &stype)
:
    Symbol(name, type, stype),
    d_status(status),
    d_value(value == DEFAULT ? s_value++ : value),
    d_association(association),
    d_priority(s_priority),
    d_literal(name),
    d_readableLiteral(name),
    d_firstSet(this)
{
    if (status == ACTIVE)
        ++s_nActive;

    if (name.find("'\\x") == 0)
    {
        char charRepresentation;
        istringstream convert(name.substr(3));
        convert >> hex >> reinterpret_cast<int &>(charRepresentation);
        if (isprint(charRepresentation))
        {
            d_readableLiteral = "'";
            d_readableLiteral.append(1, charRepresentation);
            d_readableLiteral += "'";
        }
    }
       
    lineMsg() << "Defining terminal " << d_readableLiteral << ": pri = " << 
                                                        d_priority << spool;
    if (status == ACTIVE)
        msg() << " (active: " << s_nActive << ")" << spool;

    msg() << info;

    if (d_value > s_maxValue)
        s_maxValue = d_value;
}



