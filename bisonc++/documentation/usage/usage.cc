#include <iostream>
#include <string>

using namespace std;

#include "../../VERSION"

char version[] = VERSION;
char year[] = YEARS;

#define _INCLUDED_BISONCPP_H_
#include "../../usage.cc"

int main()
{
    usage("bisonc++");
    return 0;
}
