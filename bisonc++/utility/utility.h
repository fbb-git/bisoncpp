#ifndef INCLUDED_UTILITY_
#define INCLUDED_UTILITY_

template <int value>
struct Int
{};

template <typename type>
struct Type
{};

struct DataType         // data types used by semunion: these names are 
{                       // directly available from within classes inheriting
    enum Type           // from DataType
    {
        NONE,
        INT,
        BOOL,
        STRING,
        BLOCK,
        TERMINAL,
        SYMBOL
    };
};

#endif


