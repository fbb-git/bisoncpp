#include "generator.ih"

void Generator::polymorphicInline(ostream &out) const
{
    if (not d_options.polymorphic())
        return;

    key(out);

    string const &className = d_options.className();

        // insert the inline polymorphic members

    out <<
        "namespace " << className << "Meta__\n"
        "{\n"
        "    inline Base::Base(Tag tag)\n"
        "    :\n"
        "        d_tag(tag)\n"
        "    {}\n"
        "\n"

        "    inline Tag Base::tag() const\n"
        "    {\n"
        "        return d_tag;\n"
        "    }\n"
        "\n"

        "    template <Tag tg_>\n"
        "    inline Semantic<tg_>::Semantic(\n"
        "                   typename TypeOf<tg_>::DataType const &data)\n"
        "    :\n"
        "        Base(tg_),\n"
        "        d_data(data)\n"
        "    {}\n"
        "\n"

        "    template <Tag tg_>\n"
        "    inline Semantic<tg_>::Semantic(typename TypeOf<tg_>::DataType "
                                                                    "&&tmp)\n"
        "    :\n"
        "        Base(tg_),\n"
        "        d_data(std::move(tmp))\n"
        "    {}\n"
        "\n"

        "    template <Tag tg_>\n"
        "    inline Semantic<tg_>::ReturnType Semantic<tg_>::data() const\n"
        "    {\n"
        "        return d_data;\n"
        "    }\n"
        "\n"

        "    template <Tag tg_>\n"
        "    inline Semantic<tg_>::DataType &data() \n"
        "    {\n"
        "        return d_data;\n"
        "    }\n"
        "\n"

        "    template <Tag tg_>\n"
        "    inline Semantic<tg_> const &Base::as() const\n"
        "    {\n"
        "        return dynamic_cast<Semantic<tg_> const &>(*this);\n"
        "    }\n"
        "\n"

        "    template <typename Tp_>\n"
        "    Semantic<TagOf<Tp_>::tag> *newSemantic(Tp_ const &init)\n"
        "    {\n"
        "        return new Semantic<TagOf<Tp_>::tag>(init);\n"
        "    }\n"
        "\n"

        "    template <typename Tp_>\n"
        "    Semantic<TagOf<Tp_>::tag> *newSemantic(Tp_ &&tmp)\n"
        "    {\n"
        "        return new Semantic<TagOf<Tp_>::tag>(std::move(init));\n"
        "    }\n"
        "}  // namespace " << className << "Meta__\n";
        "\n";
}








