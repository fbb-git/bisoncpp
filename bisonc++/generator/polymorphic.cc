#include "generator.ih"

void Generator::polymorphic(ostream &out) const
{
    if (not d_options.polymorphic())
        return;

    key(out);

    string const &className = d_options.className();

    out << 
        "namespace " << className << "Meta__\n"
        "{\n"
        "    enum Tag\n"                            // Tags
        "    {\n";

    for (auto &poly: d_polymorphic)
        out << "        " << poly.first << ",\n";

    out << 
        "    };\n"
        "\n"
        "    template <Tag tag>\n"                  // struct TypeOfBase
        "    struct TypeOfBase;\n"
        "\n";

    for (auto &poly: d_polymorphic)
        out << 
        "    template <>\n"
        "    struct TypeOfBase<" << poly.first << ">\n"
        "    {\n"
        "        typedef " << poly.second << " DataType;\n"
        "    };\n"
        "\n";

    out <<                                          // Class-/BasicType
        "    struct ClassType\n"
        "    {\n"
        "        char _[2];\n"
        "    };\n"
        "    \n"
        "    struct BasicType\n"
        "    {\n"
        "        char _;\n"
        "    };\n"
        "\n"
        "    template <typename T>\n"
        "    BasicType test(...);\n"
        "\n"
        "    template <typename T>\n"
        "    ClassType test(void (T::*)());\n"
        "\n"

                                   // struct TypeOf<Tag> defines DataType and
                                   // ReturnType (as value type or const &)
        "    template <Tag tg_>\n"
        "    struct TypeOf: public TypeOfBase<tg_>\n"
        "    {\n"
        "        typedef typename TypeOfBase<tg_>::DataType DataType;\n"
        "        enum: bool \n"
        "        { \n"
        "            isBasicType = "
                            "sizeof(test<DataType>(0)) == sizeof(BasicType)\n"
        "        };\n"
        "\n"
        "        typedef typename std::conditional<\n"
        "                    isBasicType, \n"
            "                    DataType, \n"
            "                    DataType const &\n"
        "                >::type ReturnType;\n"
        "    };\n"
        "\n"
        "    template <typename Tp_>\n"             // struct TagOf<Type>
        "    struct TagOf;\n"
        "\n";

    for (auto &poly: d_polymorphic)
        out << 
        "    template <>\n"
        "    struct TagOf<" << poly.second << ">\n"
        "    {\n"
        "        static Tag const tag = " << poly.first << ";\n"
        "    };\n"
        "\n";

                                                    // the Base class:
    out <<
        "    class Base\n"
        "    {\n"
        "        Tag d_tag;\n"
        "    \n"
        "        public:\n"
        "            Base(Base const &other) = delete;\n"
        "            virtual ~Base();\n"
        "            Tag tag() const;\n"
        "    \n"
        "            template <Tag tg_>\n"
        "            typename TypeOf<tg_>::ReturnType get() const;\n"
        "    \n"
        "        protected:\n"
        "            Base(Tag tag);\n"
        "    };\n"
        "    \n"
                                                    // the Semantic class:
        "    template <Tag tg_>\n"
        "    class Semantic: public Base\n"
        "    {\n"
        "        typedef typename TypeOf<tg_>::DataType DataType;\n"
        "    \n"
        "        mutable DataType d_data;\n"
        "    \n"
        "        public:\n"
        "            typedef typename TypeOf<tg_>::ReturnType ReturnType;\n"
        "    \n"
        "            Semantic(DataType const &data);\n"
        "            Semantic(DataType &&tmp);\n"
        "    \n"
        "            ReturnType data() const;\n"
        "            DataType &data();\n"
        "    };\n"
        "}  // namespace " << className << "Meta__\n"
    "\n";
}

