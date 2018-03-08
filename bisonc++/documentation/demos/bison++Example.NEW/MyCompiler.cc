#include "MyParser.h"

#include <cstdio>

int main(int argc,char **argv)
{
    MyParser aCompiler;
    int result = aCompiler.parse();
 
    printf("Parsing result = %s\n", result ? "Error" : "OK");
     return 0;
};




