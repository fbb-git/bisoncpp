#include "generator.ih"

void Generator::polymorphicDecl(ostream &out) const
{
    if (not d_options.polymorphic())
        return;

    key(out);

    out <<  
            "        template <Tag__ tag>\n"
            "        void extract__(std::string const &in);\n"
            "        template <typename Tp_>\n"
            "        void setSemantic__(Tp_ const &value);\n"
            "        template <typename Tp_>\n"
            "        void setSemantic__(Tp_ &&tmp);\n";
}


