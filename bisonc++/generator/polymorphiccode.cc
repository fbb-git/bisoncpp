#include "generator.ih"

void Generator::polymorphicCode(ostream &out) const
{
    if (not d_options.polymorphic())
        return;

    key(out);

        // static_assert(std::is_default_constructible<poly.second>::value, 
        //    "No default constructor for poly.first (poly.second)");       
    if (d_options.constructorChecks().value == Options::ON)
    {
        if (not d_options.polymorphic())
            out << "static_assert(std::is_default_constructible<STYPE__>\n" << 
                "    \"No default constructor for STYPE__\");\n";
        else
        {
            for (auto &poly: d_polymorphic)
                out <<  "static_assert(std::is_default_constructible<" << 
                                                poly.second << ">::value,\n"
                    "    \"No default constructor for " << poly.first << 
                                            " (" << poly.second << ")\");\n"
                    "\n";
        }
    }

    ifstream in;
    Exception::open(in,  d_options.polymorphicCodeSkeleton()); 

    out << "namespace Meta__\n"
           "{\n"
           "\n";

    if (d_threadSafe)
        out << "std::thread_local ";

    out << "size_t const *t_nErrors;\n";

    filter(in, out, false);
}



