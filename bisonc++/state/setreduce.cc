#include "state.ih"

void State::setReduce(Terminal const *token, Production const *production)
{
    string const &tokenName = token->display();

    ActionTableIter parsTabIterator = d_action.find(token);

    unsigned productionNr = production->nr();

    if (parsTabIterator == d_action.end())      // New reduction request
    {
        msg() << "   On " << tokenName << " reduce, using " << production << 
                info;
        d_action.insert
        (
            ActionTable::value_type
            (
                token, 
                productionNr == Rules::acceptProductionNr() ?
                    ShiftReduce(ShiftReduce::ACCEPT)
                :
                    ShiftReduce(production)
            )
        );
        return;
    }

    // Below: S/R or R/R conflict or maybe twice reducing by the same rule,
    //        which happens when this situation is seen again in new
    //        iterations. 
                
    ShiftReduce &sr = parsTabIterator->second;

    if 
    (
        sr.reported()                       // error already reported
        ||
        sr.production() == production       // or this reduction already
        ||                                  // set
            sr.accept()
            && 
            productionNr == Rules::acceptProductionNr()
    )   
        return;                             // then done.

    if (sr.acceptOrReduce())
    {
        ++s_nReduceReduceConflicts;
        ++d_nReduceReduceConflicts;
        msg() << "\n"
                "    Reduce-reduce conflict on " << tokenName << ":\n"
                "       reduce by production " << production << spool;

        if (sr.accept())
            msg() << " or ACCEPT" << info;
        else
            msg() << "\n"
                    "    or reduce by production " << sr.production() << info;

        Production const *solved;
        Production const *suppressed;

        if (production->nr() < sr.production()->nr())
        {
            solved = production;
            suppressed = sr.production();
        }
        else
        {
            solved = sr.production();
            suppressed = production;
        }

        d_suppressed.insert
        (
            ActionTable::value_type(token, ShiftReduce(suppressed))
        );
        
        msg() << "Conflict solved using the lower numbered "
                                                    "production rule (" << 
                solved->nr() << ")" << info;

        sr.setProduction(solved);
    }
    else 
        shiftReduceConflict(tokenName, sr.state(), production);

    sr.setReported();
}
