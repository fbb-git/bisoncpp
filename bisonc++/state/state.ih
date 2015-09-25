#include "state.h"

#include <string>
#include <ostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <iomanip>

#include <bobcat/mstream>
#include <bobcat/arg>
#include <bobcat/indent>

#include "../rules/rules.h"
#include "../nonterminal/nonterminal.h"
#include "../production/production.h"
#include "../item/item.h"
#include "../lookaheadset/lookaheadset.h"
#include "../stateitem/stateitem.h"

using namespace std;
using namespace FBB;

inline void State::addDependents(Next const &next, Symbol const *symbol, 
                                 size_t idx)
{
    d_itemVector[idx].setNext(Next::addToKernel(d_nextVector, symbol, idx));
}

inline std::ostream &State::skipInsertion(std::ostream &out) const
{
    return out;
}

