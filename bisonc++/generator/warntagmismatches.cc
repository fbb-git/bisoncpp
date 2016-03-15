#include "generator.ih"

void Generator::warnTagMismatches(ostream &out) const
{
    if (d_options.warnTagMismatches().triVal != Options::ON)
        return;

    key(out);

    out << 
       "std::cerr << \"Warning: requesting value of Tag \" <<\n"
       "    aTag__Name__[static_cast<int>(tag)] << \" from \"\n"
       "    get<\" << aTag__Name__[static_cast<int>(d_base->tag())] << \">()\n"
       "    \"\n\";\n";
}
