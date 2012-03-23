#include "generator.ih"

void Generator::polymorphic(ostream &out) const
{
    if (not d_options.polymorphic)
        return;

    key(out);

        // insert the Tags:

    out << 
    "        enum class Tag__\n"
    "        {\n";

    for (auto &poly: d_polymorphic)
        out << "            " << poly.first << ",\n";

    out << "        }\n;


        // insert the Base class:
class Base__
{
    Tag__ d_tag;

    public:
        Base__(Base__ const &other) = delete;
        virtual ~Base__();
        Tag__ tag() const;

        template <Tag__ tg_>
        typename Trait__<tg_>::ReturnType__ as() const;

    protected:
        Base__(Tag__ tag);
};

        // insert the 

MOVE THESE TO THE IMPLEMENTATION SECTION OF parserbase.h:

inline Tag Base__::tag() const
{
    return d_tag;
}

inline Base__::Base__(Tag tag)
:
    d_tag(tag)
{}



}
