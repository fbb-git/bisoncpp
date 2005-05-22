#ifndef _INCLUDED_BISONCPP_H_
#define _INCLUDED_BISONCPP_H_

#include <iostream>
#include <string>

#include "errno/errno.h"
#include "arg/arg.h"
#include "rules/rules.h"
#include "parser/parser.h"
#include "itemsets/itemsets.h"
#include "generator/generator.h"

using namespace std;
using namespace FBB;

extern char version[];
extern char year[];

void usage(string const &program_name);

#endif
