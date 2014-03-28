#include "generator.ih"

bool Generator::bolAtIgnore(istream &in) 
{
    string line;
    while (getline(in, line) && line[0] != '@')
        ;
    return line[0] == '@';
}
