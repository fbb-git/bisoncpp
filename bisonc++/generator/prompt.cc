#include "generator.ih"

namespace {
    char const *noPrompt = 
R"(
        if (d_debug_)
            s_out_ << '\n';
)";

    char const *doPrompt = 
R"(
        if (d_debug_)
        {
            s_out_ << "\n================\n"
                       "? " << dflush_;
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
