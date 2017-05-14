#include "generator.ih"

namespace {
    char const *noPrompt = 
R"(
        if (d_debug__)
            s_out__ << '\n';
)";

    char const *doPrompt = 
R"(
        if (d_debug__)
        {
            s_out__ << "\n================\n"
                       "? " << dflush__;
            std::string s;
            getline(std::cin, s);
        }
)";

} // anonymous namespace

void Generator::prompt(ostream &out) const
{
    key(out);

    if (d_genDebug)
        out << (d_options.prompt() ? doPrompt : noPrompt) << '\n';        
}
