#include "generator.ih"

namespace {
    char const *iftag =  
R"(
    if (tag() != tg)
    {
        if (*t_nErrors != 0)
            const_cast<SType *>(this)->assign<tg>();
        else
        {
            std::cerr << "[Fatal] calling `.get<Tag__::" << 
                idOfTag__[static_cast<int>(tg)] << 
                ">()', but Tag " <<
                idOfTag__[static_cast<int>(tag())] << " is encountered. Try "
                "option --debug and call setDebug(Parser::ACTIONCASES)\n";
            throw 1;        // ABORTs
        }
    }
)";

} // namespace

void Generator::warnTagMismatches(ostream &out) const
{
    if (d_options.tagMismatches().value != Options::ON)
        return;

    key(out);

    // idOfTag: defined by staticdata.cc

    out << iftag << '\n';
}

