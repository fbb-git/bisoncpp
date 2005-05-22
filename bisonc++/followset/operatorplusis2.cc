#include "followset.ih"

FollowSet &FollowSet::operator+=(FirstSet const &firstSet) 
{
                                    // As the elements are always Terminals, 
                                    // I can apply a reinterpret_cast here
    set<Terminal const *> const *sourceSet =     
            reinterpret_cast<set<Terminal const *> const *>(&firstSet);

    insert(sourceSet->begin(), sourceSet->end());

//        cout << "FOLLOW = ";
//        copy(begin(), end(),
//                ostream_iterator<char>(cout, " "));
//        if (hasEOF())
//            cout << "<$>";
//        cout << endl;

    return *this;
}
