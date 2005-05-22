#include "arg.ih"

Arg::Arg(char const *optstring, 
         LongOption const * const begin, LongOption const * const end,
         int argc, char **argv)
:
    d_argPointer(0)
{
    setBasename(argv[0]);

    OptStructArray optStructs(end - begin + 1); // create array of n + 1 
                                                // structs for long options

    fillLongOptions(optStructs.get(), optstring, begin, end);

    opterr = 0;                     // prevent getopt() msgs to stderr
    int longOptionIndex;       // receives the index of the long options

    while (true)
    {
        int c = getopt_long(argc, argv, optstring, optStructs.get(), 
                                                    &longOptionIndex);

        switch (c)
        {
            case EOF:
                copy(argv + optind, argv + argc, back_inserter(d_argv));
            return;

            case ':':
                throw Errno(0, 
                    "ArgData::ArgData(): missing value for option: ") <<
                    insertable << argv[optind - 1] << throwable;
            return;

            case '?':
                throw Errno(0, "ArgData::ArgData(): unknown option: ")
                    << insertable << argv[optind - 1] << throwable;
            break;

            case 0:
                if (plainLongOption(&c, begin[longOptionIndex]))
                    break;
            // FALLING THROUGH IF LONG OPTION IS ALSO SHORT CHAR OPTION
                // in which case c is set to the corresponding short
                // char option
            default:
                d_optv.push_back(IntStringPair(c, optarg ? optarg : ""));
            break;    
        }
    }
}







