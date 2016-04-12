#include "rules.ih"

void Rules::setHiddenAction(Block const &block) 
{
                                            // create (hidden) production 
                                            // (when shown, 90000 is added to
                                            // the line nr to flag a hidden
                                            // action production rule
    Production *pp = new Production(d_nonTerminal.back(), 
                                        //90000 + 
                                        s_lastLineNr);  
    // 20160412 apparently the 90000 flag is nowhere used, so I decided
    //          not to use it anymore

    d_production.push_back(pp);             // put production in production 
                                            // vector

                                            // add production to the hidden
                                            // rule
    d_nonTerminal.back()->addProduction(d_production.back());

    d_production.back()->setAction(block);
}
