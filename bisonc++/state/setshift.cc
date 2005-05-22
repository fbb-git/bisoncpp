#include "state.ih"

void State::setShift(Terminal const *token, unsigned nextStateIdx)
{
    ActionTableIter parsTabIterator = d_action.find(token);
    if (parsTabIterator == d_action.end())      // New shift requested
    {
        d_action.insert
        (
            ActionTable::value_type(token, ShiftReduce(nextStateIdx))
        );
        return;
    }

    ShiftReduce &sr = parsTabIterator->second;

        // Existing element found: Already reported or same transition as the
        // current one, then done here.
    if (sr.reported() || sr.state() == nextStateIdx)
        return;

        // Existing element in the action table. This must be a production.
        // To see whether we have a conflict, determine the production, and 
        // see if there is a disambiguating priority rule
    Production const *production = sr.production();

    Terminal const *precedence = production->precedence();
    if (!precedence)
        precedence = d_inheritedTerminal;
    else
        msg() << "Reduction rule has precedence of token " <<
                precedence->display() << info;

    msg() << "   Reduction rule terminal: " << precedence->display() << 
                " (pri: " << precedence->priority() << 
                ", assoc: " << precedence->association() << ")\n"
            "   shift-token: " << token->display() << 
                " (pri: " << token->priority() << 
                ", ass: " << token->association() << ")" << info;

    Action action;

    switch (precedence->comparePriority(token))
    {
        case Terminal::LARGER:
            action = REDUCE_RULE;
        break;

        case Terminal::SMALLER:
            action = SHIFT_TOKEN;
        break;

        case Terminal::EQUAL:
            switch (precedence->association())
            {
                case Terminal::RIGHT:
                    action = SHIFT_TOKEN;
                break;

                case Terminal::NONASSOC:
                case Terminal::LEFT:
                    action = REDUCE_RULE;
                break;

                default:    // if omitted, the compiler warns for some reason
                            // about a possibly unitialized `action' variable.
                case Terminal::UNDEFINED:
                    action = CONFLICT;
                break;
            }
        break;
    }

    if (action != CONFLICT)
    {
        msg() << "Resolving shift-reduce conflict on " << token->display() << 
                "\n"
                "   (shift to state " << nextStateIdx << 
                ", reduce using\n"
                "   production " << production << ") by " << spool;

        if (action != SHIFT_TOKEN)
            msg() << "reducing." << info;
        else
        {
            msg() << "shifting" << info;
            d_suppressed.insert(ActionTable::value_type(token, sr));
            sr.setState(nextStateIdx);
        }
    }
    else if (!sr.shift())
    {
        shiftReduceConflict(token->display(), nextStateIdx, production);

        d_suppressed.insert
        (
            ActionTable::value_type(token, ShiftReduce(production))
        );

        sr.setState(nextStateIdx);              // prefer shift over reduce
    }

    sr.setReported();                           // handled this conflict
}


