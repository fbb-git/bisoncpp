#include "writer.h"

#include <iomanip>

#include <bobcat/align>
#include <bobcat/tablesupport>
#include <bobcat/arg>

#include "../symbol/symbol.h"
#include "../terminal/terminal.h"
#include "../nonterminal/nonterminal.h"
#include "../lookaheadset/lookaheadset.h"
#include "../stateitem/stateitem.h"
#include "../state/state.h"
#include "../rules/rules.h"

using namespace std;
using namespace FBB;

