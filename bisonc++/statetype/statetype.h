#ifndef _INCLUDED_STATETYPE_
#define _INCLUDED_STATETYPE_

class StateType
{
    public:
        enum Type           // modify data.cc when this enum changes
        {
            NORMAL      = 0,
            ERR_ITEM    = 1,
            REQ_TOKEN   = 2,        // terminal shifts and multiple reductions
            DEF_RED     = 4         // state has default reduction
        };                          // Combinations may occur.

    private:
        int d_type;                 // the type of a state

        static int const s_mask = 7;        // mask for all legal Type values
        static char const  *s_stateName[];  // array of all state type names

    public:
        StateType(int type);
        int type() const;
        void setType(Type type);

        static char const *typeName(int type);
};

inline StateType::StateType(int type)
:
    d_type(type)
{}

inline int StateType::type() const
{
    return d_type;
}

inline void StateType::setType(Type type)
{
    d_type |= type;
}

inline char const *StateType::typeName(int type)
{
    return s_stateName[type & s_mask];
}

        
#endif


