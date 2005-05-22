#include "rules.ih"

void Rules::addElement(Symbol *symbolPtr)
{
    d_currentProduction->push_back(symbolPtr);

    lineMsg() << "      " << Symbol::showType(symbolPtr) << " `" << 
            symbolPtr->name() << "' ( = $" << d_currentProduction->size() <<
            ")" << info;
}
