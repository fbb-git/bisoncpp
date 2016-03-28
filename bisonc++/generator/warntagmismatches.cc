#include "generator.ih"

void Generator::warnTagMismatches(ostream &out) const
{
    if (d_options.tagMismatches().value != Options::ON)
        return;

    key(out);

    // idOfTag: defined by staticdata.cc

    out << R"(
    if (tag() != tg)
    {
        std::cerr << "[Fatal] calling `.get<Tag__::" << 
            idOfTag__[static_cast<int>(tg)] << 
            ">()', but Tag " <<
            idOfTag__[static_cast<int>(tag())] << " is available. "
            " Try option --rule-numbers\n";
        throw 1;        // ABORTs
    }
    )" << '\n';
}
