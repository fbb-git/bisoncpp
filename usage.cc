#include <iostream>
#include <string>

using namespace std;

#include "bisonc++/VERSION"

char version[] = VERSION;
char year[] = YEARS;

void usage(string const &program_name);

int main()
{
    usage("bisonc++");
    return 0;
}
