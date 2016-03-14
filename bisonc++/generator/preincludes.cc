#include "generator.ih"

void Generator::preIncludes(std::ostream &out) const
{
    bool preInclude = not d_options.preInclude().empty();
    bool polymorphic =  d_options.polymorphic();

    if (not preInclude && not polymorphic)
        return;

    key(out);

    if (preInclude)    
        out << "#include " << d_options.preInclude() << '\n';
}
