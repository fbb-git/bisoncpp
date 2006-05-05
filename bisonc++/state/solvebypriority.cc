#include "state.ih"

bool State::solveSRbyPriority(TransitionMapValue &transition, 
                              SRContext &src, ReduceMapIterator &reduceIter)
{
    Terminal const *terminal = Terminal::downcast(transition.first);
    Production const *production = reduceIter->first;

    switch (Terminal::comparePriorities(terminal, production->precedence()))
    {
        default:
        return false;

        case Terminal::SMALLER:
            msg() << indent << "Solved as REDUCE: Pri(rule " << 
                production->nr() << 
                " (= " << production->precedence()->priority() << ")) "
                "> Pri(`" << terminal->display() <<
                "' (= " << terminal->priority() << "))" 
                << info;

            transition.second->shutOff();   // shut off the shift info
            --src.state.d_nTransitions;
            --src.state.d_nTerminalTransitions;
        break;

        case Terminal::LARGER:
            msg() << indent << "Solved as SHIFT: Pri(rule #" << 
                production->nr() << 
                " (= " << production->precedence()->priority() << ")) "
                "< Pri(`" << terminal->display() <<
                "' (= " << terminal->priority() << "))" 
                << info;
                                                // don't reduce on terminal
            reduceIter->second -= terminal;
        break;
    }
    return true;
}
