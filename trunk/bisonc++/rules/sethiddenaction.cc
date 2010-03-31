#include "rules.ih"

void Rules::setHiddenAction(Block const &block) 
{
    Production *pp = new Production(d_nonTerminal.back());  // create 
                                                            // production 

    d_production.push_back(pp);             // put production in production 
                                            // vector

                                            // add production to the hidden
                                            // rule
    d_nonTerminal.back()->addProduction(d_production.back());

    d_production.back()->setAction(block);
}
