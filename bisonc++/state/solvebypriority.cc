#include "state.ih"

// bool State::solveSRbyPriority(TransitionMapValue &transition, 
//                              SRContext &src, ReduceMapIterator &reduceIter)
bool State::solveSRbyPriority(TransitionMapValue &transition, 
                              SRContext2 &src)
{
    Production const *production = src.reduction->first; //reduceIter->first;
    Terminal const *terminal = production->precedence();
    unsigned productionPriority = terminal ? terminal->priority() : 0;

    terminal = Terminal::downcast(transition.first);
    unsigned terminalPriority = terminal->priority();

    switch (Terminal::comparePriorities(terminal, production->precedence()))
    {
        default:
        return false;

        case Terminal::SMALLER:
            msg() << indent << "Solved as REDUCE: Pri(rule " << 
                production->nr() << 
                " (= " << productionPriority
                            /*production->precedence()->priority()*/
                 << ")) "
                "> Pri(`" << terminal->display() <<
                "' (= " << terminalPriority
                << "))" 
                << info;

            transition.second->shutOff();   // shut off the shift info
            --src.state.d_nTransitions;
            --src.state.d_nTerminalTransitions;
        break;

        case Terminal::LARGER:
            msg() << indent << "Solved as SHIFT: Pri(rule #" << 
                production->nr() << 
                " (= " <<  productionPriority
                            /*production->precedence()->priority()*/
                << ")) "
                "< Pri(`" << terminal->display() <<
                "' (= " <<  terminalPriority 
                << "))" 
                << info;
                                                // don't reduce on terminal
            src.reduction->second -= terminal;
//            reduceIter->second -= terminal;
        break;
    }
    return true;
}
