#include "production.ih"

size_t Production::s_nr;
bool Production::s_unused;

Production const *Production::s_startProduction;

vector<string> Production::s_fileName;
