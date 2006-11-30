#include <iostream>
#include <string>

using namespace std;

#include "../../VERSION"

char version[] = VERSION;
char year[] = YEARS;

#include "../../usage.cc"

int main()
{
    usage("bisonc++");
    return 0;
}
