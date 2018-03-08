#include "parser.ih"

// unused ruleType is required when initializing s_defaultAction in data.cc

void Parser::blkNopW([[maybe_unused]] string const &ruleType, 
                     Production const &prod)
{
    wmsg << '`' << &prod << 
            "': no default action block was installed" << endl;
}
