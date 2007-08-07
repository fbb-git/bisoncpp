#include "rules.ih"

void Rules::addElement(Symbol *symbol)
{
    d_currentProduction->push_back(symbol);

    lineMsg() << "      $"  << d_currentProduction->size() << ": " <<
                        symbol << info;
}
