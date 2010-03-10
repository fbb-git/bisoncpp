#include "nonterminal.ih"

        // For an empty production, the N gets <empty>. For non-empty
        // productions: add those element's first symbols, and stop if an
        // element has no empty production. If, at the end, the final element
        // has an empty production, add <empty> as well

void NonTerminal::setFirst(NonTerminal *nonTerminal)
{
    FirstSet &firstSet = nonTerminal->d_first;
    Production::Vector &prodVect = nonTerminal->d_production;

    if (!prodVect.size())               // empty production
        firstSet.addEpsilon();          // add epsilon to FirstSet
    else
    {
        bool hasEpsilon = false;        // include epsilon at the end?

        for                             // visit all elements of a production
        (
            Production::Vector::const_iterator it = prodVect.begin(); 
                it != prodVect.end(); 
                    ++it
        )    
        {
            Production const &production = **it;

            bool epsilon = true;        // epsilon in this rule's elements
            for 
            (
                auto symPtrIt = production.begin();
                    symPtrIt != production.end();
                        ++symPtrIt
            )
            {
                firstSet += (*symPtrIt)->firstSet();
                                        // add the element's firstSet
    
                                        // element without <e>
                if (!(*symPtrIt)->firstSet().hasEpsilon())
                {
                    epsilon = false;
                    break;              // and done, this productionrule
                }
            }
            hasEpsilon |= epsilon;      // once a production rule includes
                                        // epsilon, hasEpsilon remains true
        }
        if (hasEpsilon)
            firstSet.addEpsilon();
        else
            firstSet.rmEpsilon();
    }

    s_counter += firstSet.setSize();
}




