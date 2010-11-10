/*
                              driver.cc
*/

#include "driver.h"

#include "../inputgrammar.h"

using namespace std;
using namespace FBB;


int main(int argc, char **argv, char **envp)
{
    Arg &arg = Arg::initialize("", argc, argv);

    InputGrammar input;

    input.parse();

    return 0;
}
