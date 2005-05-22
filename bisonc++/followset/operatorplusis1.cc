#include "followset.ih"

FollowSet &FollowSet::operator+=(FollowSet const &other) 
{
    insert(other.begin(), other.end());
    d_EOF |= other.d_EOF;

//        cout << "FOLLOW = ";
//        copy(begin(), end(),
//                ostream_iterator<char>(cout, " "));
//        if (hasEOF())
//            cout << "<$>";
//        cout << endl;

    return *this;
}
