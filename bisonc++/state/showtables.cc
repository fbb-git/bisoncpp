#include "state.ih"

void State::showTables(State const *pState) 
{
    if (pState->d_inheritedTerminal != Rules::defaultTerminal())
        msg() << "State " << pState->d_idx << " (inherited terminal: " << 
                pState->d_inheritedTerminal->display() << ")\n" << 
                info;
    else
        msg() << "State " << pState->d_idx << "\n" << 
                info;

    pState->showKernel();
    pState->showNonKernel();

    pState->showActions();
    pState->showGoTo();

    if (pState->d_defaultReduction)
        msg() << "\n"
                "    _default_:   reduce, using production\n" << 
                setw(12) << " " << pState->d_defaultReduction << info; 

    pState->showSuppressed();

    msg() << info;
}
