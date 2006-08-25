#include <iostream>
#include <string>

using namespace std;

#include "../../VERSION"
#include "../../usage.cc"

char version[] = VERSION;
char year[] = YEARS;

int main()
{
    usage("bisonc++");
    return 0;
}
