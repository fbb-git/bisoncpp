//#include "atdollar.ih"
//
//void AtDollar::memberSelectorPatterns()
//{
//    switch (d_text[1])
//    {
//        case '$':
//            d_pattern = DDm;
//        return;
//
//        case '<':
//            d_pattern = Dt_m;
//            setTagNr(2);
//        return;
//
//        default:
//            d_nr = stol(d_text.substr(1));
//            d_pattern = d_nr < 0 ? D_m : Dnm;
//        return;
//    }
//}
