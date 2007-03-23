#ifndef _INCLUDED_STATETYPE_
#define _INCLUDED_STATETYPE_

class StateType
{
    public:
        enum Type           // modify data.cc when this enum changes
        {
            NORMAL,
            HAS_ERROR_ITEM,
            IS_ERROR_STATE,
            NEEDS_LOOKAHEAD,
        };    

    private:
        Type                d_type;

        static char const  *s_stateName[];

    protected:
        StateType(Type type);

    public:
        Type type() const;
        char const *typeName() const;
        void setType(Type type);

};

inline StateType::Type StateType::type() const
{
    return d_type;
}

inline void StateType::setType(Type type)
{
    d_type = type;
}

inline StateType::StateType(Type type)
:
    d_type(type)
{}

inline char const *StateType::typeName() const
{
    return s_stateName[d_type];
}

        
#endif


