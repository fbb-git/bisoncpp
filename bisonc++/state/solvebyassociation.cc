#include "state.ih"

// bool State::solveSRbyAssociation(TransitionMapValue &transition, 
//                               SRContext &src, ReduceMapIterator &reduceIter)
bool State::solveSRbyAssociation(TransitionMapValue &transition, 
                              SRContext2 &src)
{
    Terminal const *terminal = Terminal::downcast(transition.first);

    switch (terminal->association())
    {
        default:
        return false;

        case Terminal::NONASSOC:
        case Terminal::LEFT:
            msg() << indent << "Solved as REDUCE using rule #" << 

//                            reduceIter->first->nr() << ". `" << 
                            src.reduction->first->nr() << ". `" << 

                            terminal->display() <<
                            "' is left- or non-associative" <<  info;

            transition.second->shutOff();   // shut off the shift info
            --src.state.d_nTransitions;
            --src.state.d_nTerminalTransitions;
        break;

        case Terminal::RIGHT:
            msg() << indent << "Solved as SHIFT. Next state: " << 
                transition.second->next() << ". `" << terminal->display() <<
                "' is right-associative" << info;

                                                // don't reduce on terminal
            src.reduction->second -= terminal;
//            reduceIter->second -= terminal;
        break;
    }
    return true;
}

