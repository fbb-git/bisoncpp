#include "generator.ih"

void Generator::polymorphicCode(ostream &out) const
{
    bool checkDefaultConstructors = d_options.checkDefaultConstructors();

    if (not d_options.polymorphic())
    {
        if (checkDefaultConstructors)
            wmsg << 
                "Default constructor checks only available "
                    "with %polymorphic" << flush;
        return;
    }

    key(out);


        // static_assert(std::is_default_constructible<poly.second>::value, 
        //    "No default constructor for poly.first (poly.second)");       
    for (auto &poly: d_polymorphic)
        out <<  "static_assert(std::is_default_constructible<" << 
                                                poly.second << ">::value,\n"
                "    \"No default constructor for " << poly.first << 
                                            " (" << poly.second << ")\");\n"
                "\n";

    ifstream in;
    Exception::open(in,  d_options.polymorphicCodeSkeleton()); 

    filter(in, out, false);
}



