#include "reductions.ih"


void Reductions::insert(Symbol const *sp, Production const *production)
{
    ++d_count;                          // count this reduction

    unsigned nr = production->nr();
    bool is_default_ = sp == Rules::defaultTerminal();

                                        // see if an element already uses this
                                        // production
    TransitionVector::iterator transition = 
            find_if(d_transitions.begin(), d_transitions.end(), 
                    Wrap1c<Transition, unsigned, bool>
                          (&Reductions::findProduction, nr));

    if (transition == d_transitions.end())      // new production
        transition = d_transitions.insert(transition, Transition(nr));

    if(is_default_)
        transition->setDefault();
    else
        transition->push_back(sp);
                                        // this reduction is either a default
                                        // transition or it uses a non-default
                                        // token: if so count another explicit
                                        // token
    if (is_default_)
    {
        d_defaultReduction = transition - d_transitions.begin();
        msg() << "   Default reduction by rule " << defaultReduction() <<
                info;
    }
    else
    {
        d_nTokens += Terminal::downcast(sp)->status() == Terminal::ACTIVE;
        msg() << "   On token " << sp->display() << " reduce by rule " << nr <<
                 ". token count = " << d_nTokens << 
                 info;
    }
}









