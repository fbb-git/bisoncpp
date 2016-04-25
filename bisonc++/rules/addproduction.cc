#include "rules.ih"

void Rules::addProduction(size_t lineNr)
{
    if (d_currentRule == 0)                             // there may be no 
        return;                                         // rule (cf. Justin
                                                        // Madru's grammar in
                                                        // the changelog. In
                                                        // that case there's
                                                        // also no production.

// cerr << "addProduction: PRODUCTION at line " << lineNr << '\n';

    updateDefaultActionLineNr(lineNr);

    s_lastLineNr = lineNr;

                                                        // create production
    d_currentProduction = new Production(d_currentRule, lineNr);

    d_production.push_back(d_currentProduction);        // put production in
                                                        // production  vector

    d_currentRule->addProduction(d_currentProduction);  // add production to 
                                                        // current rule.

//  imsg.setLineNr(lineNr);
//  imsg << "  Adding production rule " << 
//              d_currentRule->nProductions() << 
//              " (" << d_production.size() << " productions in total)" << 
//              endl;
}


