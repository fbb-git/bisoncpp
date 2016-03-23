#include "generator.ih"

void Generator::warnTagMismatches(ostream &out) const
{
    if (d_options.tagMismatches().value != Options::ON)
        return;

    key(out);

    // idOfTag: defined by staticdata.cc

    out << R"(
    if (d_base->tag() != tag)
        std::cerr << "[Warning] requesting value of Tag " <<
            idOfTag__[static_cast<int>(tag)] << " from Tag " <<
            idOfTag__[static_cast<int>(d_base->tag())] << '\n';
    )" << '\n';
}
