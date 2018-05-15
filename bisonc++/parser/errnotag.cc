#include "parser.ih"

// Unused parameters are required for the initialization of s_single in
// data.cc 

bool Parser::errNoTag([[maybe_unused]] int nElements, 
                      [[maybe_unused]] Block &block, AtDollar const &atd)
{
    stdEmsg(atd) << "the STYPE_ semantic value type does not support "
                    "tags (`" << atd.text() << "')" << endl;

    return false;
}
