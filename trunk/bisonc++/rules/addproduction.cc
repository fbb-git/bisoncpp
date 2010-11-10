#include "rules.ih"

void Rules::addProduction()
{
    if (d_currentRule == 0)                             // there may be no 
        return;                                         // rule (cf. Justin
                                                        // Madru's grammar in
                                                        // the changelog. In
                                                        // that case there's
                                                        // also no production.

    d_currentProduction = new Production(d_currentRule);// create production

    d_production.push_back(d_currentProduction);        // put production in
                                                        // production  vector

    d_currentRule->addProduction(d_currentProduction);  // add production to 
                                                        // current rule.

// If this line is to be shown (it isn't in bisonc++ 2.8.0) then pass the
// linenr from parser/openrule.cc, parser/parse.cc and rules/augmentgrammar.cc
//
//  imsg.setLineNr(lineNr);
//  imsg << "  Adding production rule " << 
//              d_currentRule->nProductions() << 
//              " (" << d_production.size() << " productions in total)" << 
//              endl;
}


