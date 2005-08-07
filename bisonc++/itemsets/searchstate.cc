#include "itemsets.ih"

void ItemSets::searchState(Symbol const *value, SSContext &context)
{
        // Walk along each of the grammar's symbols. If the goto() set
        // from `state' to that symbol (stored at value.first) is not empty
        // and unique, add it to d_state

    Symbol const &symbol = *value;  // the grammatical symbol currently under 
                                    // consideration (and its info object)

    msg() << "Inspecting " << symbol.display() << info;

        // in goTo() check for productions having end-dots. For those
        // having end-dots, make action to `reduce'
        // goTo() returns true if we also have kernel rules with intermediate
        // dots.
    State *dest = new State;

    if (context.obj.goTo(dest, context.state, symbol))     
    {
        // Shift to a state j if the current state (i.e., `dest') contains a
        // rule having a  `. symbol' and goto current-state, symbol = state j
        // in that case, state j will have a kernel item `symbol .'

        // See if we already have this state. If that is the case, then
        // we won't add it as a new state. This may not happen, but maybe
        // later, when we're going to merge kernel states.


        unsigned nextStateIdx = 0;

        while 
        (
            nextStateIdx != context.obj.d_state.size() 
            && 
            not (*context.obj.d_state[nextStateIdx] == *dest)
        )
            ++nextStateIdx;

        // at this point we have a state to go to for a rule in `state'.
        // So, the action will be `shift' to that state (if symbol is a T) 
        // AND the current rule has `. symbol' in its rhs.
        // Set the goto to that state, if its symbol is a non-terminal symbol.
        
        // when determining the next state, see if the next state's
        // lookahaed set associated with the item needs enlargement. If so, do
        // it, and flag the enlargement if the target state already exists.

        if (symbol.isTerminal() && dest->beforeDot(symbol))
        {
            msg() << "   On " << symbol.display() << " shift to state " << 
                     nextStateIdx << info;

            dest->setShiftTerminal(symbol);          // found new state
            context.state.setShift(Terminal::downcast(&symbol), nextStateIdx);
        }
        else
        {
            // The GoTo rules are for the N-symbols, and are ok.

            msg() << "   On " << symbol.display() << " goto state " << 
                    nextStateIdx << info;

            msg() << "State's inherited terminal: " <<
                    context.state.inheritedTerminal()->display() << info;

            dest->setShiftTerminal(context.state);
            context.state.setGoto(NonTerminal::downcast(&symbol), 
                                                                nextStateIdx);
        }

        if (nextStateIdx != context.obj.d_state.size())
            context.obj.checkLookaheads(nextStateIdx, context.state, symbol);
        else
        {
            msg() << "\n"
                    "State " << context.obj.d_state.size() << " added\n"
                    "inherited terminal = " << 
                    dest->inheritedTerminal()->display() << info;

            dest->setIdx(context.obj.d_state.size());
            context.obj.d_state.push_back(dest);
            return;
        }
    }
    delete dest;
}



