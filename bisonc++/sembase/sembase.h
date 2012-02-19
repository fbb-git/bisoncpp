#ifndef INCLUDED_SEMBASE_
#define INCLUDED_SEMBASE_

#include <type_traits>
#include <iosfwd>
class Block;
class Terminal;
class Symbol;

enum class Tag          // defines the various semantic values
{                       // Tags are used to instantiate the proper 
    BOOL,               // Semantic type, deriving from a polymorphic base 
    SIZE_T,             // class
    STRING,
    BLOCK,
    TERMINAL,
    SYMBOL
};

    // In separate anonymous namespace sections parts of the various semantic
    // types are defined. Sections labeled 'IUO' are `Internal Use Only' and
    // contain no serviceable parts

namespace {     // IUO

    struct Mutable                          // Semantic values may or may
    {                                       // not be mutable. By deriving
        enum: bool { isMutable = true };    // BasicTrait, below, from
    };                                      // either Mutable or Immutable
                                            // this trait is associated with 
    struct Immutable                        // a semantic value BasicTrait.
    {
        enum: bool { isMutable = false };
    };
}

    // The various semantic value types are defined in the following anonymous
    // namespace section.
    // 
    // For each semantic value type define a BasicTrait specialization which
    // is either derived from Immutable (in which case the Parser cannot
    // change the semantic value) or from Mutable (In which case changing the
    // semantic value on the semantic value stack *is* allowed)
    // In addition, define the data type to use, as received in the
    // initialization (e.g., std::string, bool, Terminal *).
    // In Bisonc++'s parser all semantic values except for Block are
    // maintained elsewhere, hence only Block is stored as object in the
    // semantic value: when spSemBase calls SemBase's destructor, the Block
    // is destroyed by Semantic<Tag::BLOCK>'s destructor.
namespace {
    template <Tag tag>
    struct BasicTrait;

    template <>
    struct BasicTrait<Tag::STRING>: public Immutable
    {
        typedef std::string DataType;
    };

    template <>
    struct BasicTrait<Tag::BOOL>: public Immutable
    {
        typedef bool DataType;
    };

    template <>
    struct BasicTrait<Tag::SIZE_T>: public Immutable
    {
        typedef size_t DataType;
    };

    template <>
    struct BasicTrait<Tag::BLOCK>: public Mutable
    {
        typedef Block DataType;
    };

    template <>
    struct BasicTrait<Tag::TERMINAL>: public Immutable
    {
        typedef Terminal *DataType;
    };

    template <>
    struct BasicTrait<Tag::SYMBOL>: public Immutable
    {
        typedef Symbol *DataType;
    };
}

    // In this section of the anonymous namespace it is determined whether a
    // semantic value type is a basic type (in which case the return type of
    // the Semantic class's conversion operator can be equal to the type
    // itself) or a class-type (in which case a reference is returned).
   /// Its logic is based on two function templates 'test' expecting either
    // any type of argument or expecting a pointer to a member function of the
    // type provided to the template. Since basic types have no members, the
    // `any argument' variant is selected by the compiler for basic
    // types. These two functions return values having different sizes,
    // allowing the template to determine whether the type is a basic type or
    // not. The enum value 'isBasicType' is initialized accordingly.
   /// For the ReturnType (i.e., the conversion operator's return type the
    // std::conditional template meta programming function is used. For a
    // mutable data type a reference to the Semantic class's data memebr is
    // returned, for an immutable basic data type a copy of the data member's
    // value is returned, otherwise a const & is returned.
namespace {
    struct C2
    {
        char _[2];
    };
    
    struct C1
    {
        char _;
    };

    template <typename T>
    C1 test(...);

    template <typename T>
    C2 test(void (T::*)());

    template <Tag tg_>
    struct Trait: public BasicTrait<tg_>
    {
        typedef typename Trait<tg_>::DataType DataType;
        enum: bool 
        { 
            isMutable = Trait<tg_>::isMutable,
            isBasicType = sizeof(test<DataType>(0)) == sizeof(C1)
        };

        typedef typename
            std::conditional<
                isMutable,
                    DataType &,
                    typename std::conditional<
                        isBasicType, 
                            DataType, 
                            DataType const &
                    >::type
            >::type ReturnType;
    };
}

   /// The implementation of the polymorphic semantic value in fact implements
    // a type-safe polymorphic semantic union. This is a non-existing data
    // type in C++, but the parser may handle semantic values as unions: it
    // always knows the actual type of semantic value that's used at a
    // particular point in the grammar, and if not, it can inspect the
    // SemBase's tag fields. Since the parser knows, or can determine what the
    // actual semantic type is, it can always perform a downcast, resulting in
    // a *very* lightweight SemBase base class: there's only a virtual
    // destructor. No other virtual members are required. Downcasting itself
    // is encapsulated in its 'as' member, allowing constructions like
   ///      $1->as<Tag::STRING>() 
   /// to downcast the $1 SemBase to a Semantic<Tag::STRING>, and then,
    // usually by implication, to a std::string, using the Semantic's
    // conversion operator. 
class SemBase
{
    Tag d_tag;

    public:
        SemBase(SemBase const &other) = delete;
        virtual ~SemBase();
        Tag tag() const;

        template <Tag tg_>
        typename Trait<tg_>::ReturnType as() const;

    protected:
        SemBase(Tag tag);
};

inline Tag SemBase::tag() const
{
    return d_tag;
}

inline SemBase::SemBase(Tag tag)
:
    d_tag(tag)
{}

    // The Semantic class template is derived from SemBase. It always defines
    // its data member as mutable (I can't do this under template control, but
    // I could define, e.g., two anonymous structs holding, respectively, a
    // mutable and non-mutable DataType data member, but Semantic isn't doing
    // anything with d_data anyway, so by always declaring d_data as mutable
    // it can be returned from the conversion operator, which itself is a
    // const member.
   /// Again: Semantic is extremely light-weight. Only initialization and
    // conversion to the embedded data member need to be supported.
template <Tag tg_>
class Semantic: public SemBase
{
    typedef typename Trait<tg_>::DataType DataType;
    enum: bool { isMutable = Trait<tg_>::isMutable };

    mutable DataType d_data;

    public:
        typedef typename Trait<tg_>::ReturnType ReturnType;

        Semantic(DataType const &data)
        :
            SemBase(tg_),
            d_data(data)
        {}

        operator ReturnType() const
        {
            return d_data;
        }
};

    // The 'as' member simply performs the required downcast. It is
    // implemented here, since it refers to Semantic<Tag>. Since this class
    // has just been defined, no forward declaration is required anymore.
template <Tag tg_>
inline typename Trait<tg_>::ReturnType SemBase::as() const
{
    return dynamic_cast<Semantic<tg_> const &>(*this);
}
    
#endif




