//#include "lookaheadset.ih"
//
//void LookaheadSet::basicLAset(unordered_set<int> &laSet) const
//{
//    for (auto const *token: *this)
//    {
//        if (token->value() != 0)        // 0 = _error_, which is ignored in 
//            lsSet.insert(token->value()); // the LA set
//            out << token << ", ";
//    }
//
//    if (hasEOF())
//        laSet.insert(_EOF_);
//}
