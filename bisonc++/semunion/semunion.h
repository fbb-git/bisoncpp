#ifndef INCLUDED_SEMUNION_H_
#define INCLUDED_SEMUNION_H_

#include <string>

#include "../utility/utility.h"
#include "../block/block.h"
#include "../terminal/terminal.h"
#include "../symbol/symbol.h"

template <>
struct Type<int>                        // define 'DataType'
{                                               // given int
    enum { dataType = DataType::INT };
};

template <>                                     // defining 'int'
struct Type<Int<DataType::INT>>                // given INT
{
    typedef int type;
};

template <>
struct Type<bool>                        // define 'DataType'
{                                               // given bool
    enum { dataType = DataType::BOOL };
};

template <>                                     // defining 'bool'
struct Type<Int<DataType::BOOL>>                // given BOOL
{
    typedef bool type;
};

template <>
struct Type<std::string>                        // define 'DataType'
{                                               // given String
    enum { dataType = DataType::STRING };
};

template <>                                     // defining 'String'
struct Type<Int<DataType::STRING>>                // given STRING
{
    typedef std::string type;
};

template <>
struct Type<Block>                        // define 'DataType'
{                                               // given Block
    enum { dataType = DataType::BLOCK };
};

template <>                                     // defining 'Block'
struct Type<Int<DataType::BLOCK>>                // given BLOCK
{
    typedef Block type;
};

template <>
struct Type<Terminal *>                        // define 'DataType'
{                                               // given Terminal
    enum { dataType = DataType::TERMINAL };
};

template <>                                     // defining 'Terminal'
struct Type<Int<DataType::TERMINAL>>                // given TERMINAL
{
    typedef Terminal *type;
};

template <>
struct Type<Symbol *>                        // define 'DataType'
{                                               // given Symbol
    enum { dataType = DataType::SYMBOL };
};

template <>                                     // defining 'Symbol'
struct Type<Int<DataType::SYMBOL>>                // given SYMBOL
{
    typedef Symbol *type;
};



// To add a new union member:
//      - add an enum value to utility.h for the new data type
//      - the new member's class must define two Type specializations like
//          the ones just given for TEXT 
//      - add a field for the new type
//      - add the field's destructor call to ~SemUnion
class SemUnion: public DataType
{
    Type d_index;

    union
    {
        int         d_int;
        bool        d_bool;
        std::string d_str;
        Block       d_block;
        Terminal    *d_terminal;
        Symbol      *d_symbol;
    };

    public:
        SemUnion();
        SemUnion(SemUnion const &other);        // 1

        template <typename Type>
        SemUnion(Type const &value);
    
        ~SemUnion();

        template <Type dataType>
        typename ::Type<Int<dataType>>::type &value();

        Type index() const;

    private:
        template <typename Type>
        Type const *conversion() const;
        void verify(Type request);
};

inline SemUnion::SemUnion()
:
    d_index(NONE)
{}

inline DataType::Type SemUnion::index() const
{
    return d_index;
}

template <typename Tp>
inline SemUnion::SemUnion(Tp const &value)
:
    d_index(static_cast<Type>(::Type<Tp>::dataType))
{
    new (&d_int) Tp(value);
}

template <typename Type>
inline Type const *SemUnion::conversion() const
{
    return reinterpret_cast<Type const *>(&d_int);
}

template <DataType::Type dataType>
typename ::Type<Int<dataType>>::type &SemUnion::value()
{
    verify(dataType);
    return *const_cast<typename ::Type<Int<dataType>>::type *>(
                conversion<typename ::Type<Int<dataType>>::type>());
}
        
#endif
