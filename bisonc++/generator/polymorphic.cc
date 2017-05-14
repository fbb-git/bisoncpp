#include "generator.ih"

void Generator::polymorphic(ostream &out) const
{
    if (not d_options.polymorphic())
        return;

    key(out);

    out <<                                        // Tags
        "enum " << (d_options.strongTags() ? "class " : "") << "Tag__\n"
        "{\n";

    for (auto &poly: d_polymorphic)
        out << "    " << poly.first << ",\n";

    out << 
        "};\n"
        "\n"
        "namespace Meta__\n"
        "{\n"
        "\n"
        "extern ";

    if (d_threadSafe)
        out << "std::thread_local ";

    out << "size_t const *t_nErrors;\n";

    ifstream in;
    Exception::open(in,  d_options.polymorphicSkeleton()); 

    filter(in, out, false);
}

