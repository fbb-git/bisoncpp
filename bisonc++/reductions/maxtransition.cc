#include "reductions.ih"

//  struct MaxTransition
//  {
//      unsigned max;
//      Transitions *maxTrans;
//  };

void Reductions::maxTransition(Transition &trans, MaxTransition &context)
{
    if (trans.size() > context.max)
    {
        context.max = trans.size();
        context.maxTrans = &trans;
    }
}
