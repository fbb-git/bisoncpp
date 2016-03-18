//#include "options.ih"
//
//// static
//void Options::warnNonPolymorphic(OptInfo &info, char const *name)
//{
//    if (info.lineNr == 0)
//    {
//        Global::plainWarnings();
//        wmsg << "option --";
//    }
//    else
//    {
//        wmsg.setTag(info.filename + ": warning");
//        wmsg.setLineNr(info.lineNr);
//        wmsg << "directive %";
//    }
//
//    wmsg << name << " ignored:\n"
//                    "    only available for %polymorphic" << endl;
//    info.value = UNKNOWN;
//}
