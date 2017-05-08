#include "generator.ih"

void Generator::prompt(ostream &out) const
{
    key(out);

    if (d_genDebug)
    {
        if (not d_options.prompt())
            out << R"(s_out << '\n';)" << '\n';
        else
            out << 
    // BEGIN RAW STRING LITERAL
    R"(
    if (d_debug__)
    {
        s_out__ << "================\n"
                   "? " << dflush__;
        std::string s;
        getline(std::cin, s);
    }
)"  
    // END RAW STRING LITERAL
            << '\n';        
    }
}
