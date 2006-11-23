#include <iostream>
#include <string>

using namespace std;

#include "../../VERSION"

#define _INCLUDED_BISONCPP_H_

#include "../../usage.cc"

char version[] = VERSION;
char year[] = YEARS;

int main()
{
    usage("bisonc++");
    return 0;
}
