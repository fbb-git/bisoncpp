//#include "parser.ih"
//
//// called from handleDollar: the appropriate semantic value (either d_val__ or
//// d_vsp__[idx] has already been set by handleDollar. This function merely has
//// to inspect tags, if necessary.
//
//    // $$               no deref, no members: OK
//    // $-?NR 
//
//    // ($$)             deref: requires TAG
//    // ($NR) 
//    // ($<ID>-NR)              TAG assumed correct
//
//    // $$.              members: requires TAG
//    // $$-> 
//    // $NR. 
//    // $NR->
//    // $<ID>-NR.                 TAG assumed correct
//    // $<ID>-NR->
//
//string Parser::returnPolymorphic(AtDollar const &atd) const
//{
//    string ret;
//
//    bool callsMember = atd.callsMember();
//
//                        // nothing to do for $$, $-?NR: use semvals as is. 
//    if (not callsMember && atd.type() != AtDollar::DEREF)
//        return ret;
//
//    int nr = atd.nr();
//    string const *tag;        // will point to the element's tag name
//
//    if (nr < 0)   // current production rule element
//        tag = &atd.tag();
//    else
//    {
//        tag = &productionTag(nr);
//        if (tag->empty())
//        {
//            emsg <<  '`' << &d_rules.lastProduction() << 
//                "': " << atd.text() << " requires a tagged rule element" <<
//                                                                        endl;
//            return ret;
//        }
//    }
//
//    ret = ".get<Tag__::" + *tag + ">()";
//
//    if (callsMember)            // add a . if a semval's member is called
//        ret += atd.suffix();
//
//    return ret;
//}
