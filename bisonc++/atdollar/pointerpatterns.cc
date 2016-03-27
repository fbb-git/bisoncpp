//#include "atdollar.ih"
//
//void AtDollar::pointerPatterns()
//{
//    switch (d_text[1])
//    {
//        case '$':
//            d_pattern = DDp;
//        return;
//
//        case '<':
//            d_pattern = Dt_p;
//            setTagNr(2);
//        return;
//
//        default:
//            d_nr = stol(d_text.substr(1));
//            d_pattern = d_nr < 0 ? D_p : Dnp;
//        return;
//    }
//}
