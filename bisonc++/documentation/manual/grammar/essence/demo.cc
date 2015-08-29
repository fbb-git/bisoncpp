#include <iostream>

using namespace std;

struct SType
{
    int x = 123;

    template <typename Tp_>
    inline SType &operator=(Tp_ &&rhs);
};

template <bool, typename Tp_>
struct Assign;

template <typename Tp_>
struct Assign<true, Tp_>
{
    static SType &assign(SType *lhs, Tp_ &&tp);
};

template <typename Tp_>
struct Assign<false, Tp_>
{
    static SType &assign(SType *lhs, Tp_ const &tp);
};

template <>
struct Assign<false, SType>
{
    static SType &assign(SType *lhs, SType const &tp);
};

template <typename Tp_>
inline SType &Assign<true, Tp_>::assign(SType *lhs, Tp_ &&tp)
{
    cout << "move assignment of some rhs type\n";
    lhs->x = tp;
    return *lhs;
}

template <typename Tp_>
inline SType &Assign<false, Tp_>::assign(SType *lhs, Tp_ const &tp)
{
    cout << "std assign of some rhs type\n";
    lhs->x = tp;
    return *lhs;
}

inline SType &Assign<false, SType>::assign(SType *lhs, SType const &tp)
{
    cout << "Assignment of Stype to Stype through copy-assignment\n";
    lhs->x = tp.x;
    return *lhs;
}

template <typename Tp_>
inline SType &SType::operator=(Tp_ &&rhs) 
{
    return Assign<
                // the is_rvalue_reference is needed to set the first template
                // param. true, resuling in move assignment, using the first
                // overload: 
                // Assign<true, Tp_>::assign(SType *lhs, Tp_ &&tp)
                std::is_rvalue_reference<Tp_ &&>::value, 

                // the rm ref. is needed to distinguish
                // Assign<false, Tp_>::assign(SType *lhs, Tp_ const &tp) and
                // Assign<false, SType>::assign(SType *lhs, SType const &tp)
                typename std::remove_reference<Tp_>::type

           >::assign(this, std::forward<Tp_>(rhs));
}

// ====================================================================

double fact()
{
    return 3.14;
}

int main()
{
    SType st;

    int x = 10;

    st = st;
    cout << st.x << '\n';

    st = x;
    cout << st.x << '\n';


    st = int(5);
    cout << st.x << '\n';

    st = fact();
    cout << st.x << '\n';
}



