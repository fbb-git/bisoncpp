#include "bisonc++.h"

void usage(string const &program_name)
{
    cout << 
    "\n" <<
    program_name << " by Frank B. Brokken (f.b.brokken@rug.nl)\n"
    "\n"
    "LALR(1) Parser Generator V "  << version << "\n"
    "Copyright (c) GPL " << year << ". NO WARRANTY.\n"
    "Designed after `bison++' (1.21.9-1) by Alain Coetmeur "
                                                "<coetmeur@icdc.fr>\n"
    "\n"
    "Usage: " << program_name << " [OPTIONS] file\n"
    "Where:\n"
    "  [OPTIONS] - zero or more optional arguments (int options between\n"
    "              parentheses. Short options require arguments if their\n"
    "              long option variants do too):\n"

    "   --baseclass-preinclude=<header> (-H):\n"
    "           preinclude header in the base-class header file.\n"
    "           Use [header] to include <header>, otherwise \"header\"\n"
    "           will be included.\n"

    "   --baseclass-skeleton=<skeleton> (-B):\n"
    "           location of the baseclass header skeleton\n"

    "   --baseclass-header=<header> (-b):\n"
    "           filename holding the base class definition.\n"

    "   --class-skeleton=<skeleton> (-C):\n"
    "           location of the class header skeleton\n"

    "   --class-header=<header> (-c):\n"
    "           filename holding the parser class definition.\n"

    "   --construction:\n"
    "           write details about the grammar analysis to stdout.\n"

    "   --debug: generates #define DEBUG 1 in the parse function's source\n"

    "   --filenames=<filename> (-f):\n"
    "           filename of output files (overruling the default filename)\n"

    "   --force-class-header: overwrite an existing class header file\n"

    "   --force-implementation-header: overwrite an existing implementation\n"
    "           header file\n"

    "   --help (-h): produce this information (and terminate)\n"

    "   --implementation-skeleton=<skeleton> (-I):\n"
    "           location of the implementation header skeleton\n"

    "   --implementation-header=<header> (-i):\n"
    "           filename holding the implementation header.\n"

    "   --lines (-l): put #line directives in generated output\n"

    "   --namespace <namespace>, (-n):\n"
    "            define the parser in the mentioned namespace\n"

    "   --no-baseclass-header: don't create the parser's base class header\n"

    "   --no-parse-member: don't create the member parse()\n"

    "   --parser-skeleton=<parserskel> (-P):\n"
    "           location of the parse function's skeleton\n"

    "   --parser-source=<source> (-p):\n"
    "          filename holding the parse function's source.\n"

    "   --scanner=<header-file> (-s):\n"
    "          include `header-file' declaring the class Scanner, and call\n"
    "          d_scanner.yylex() in lex()\n"

    "   --show-filenames:\n"
    "          show the names of the used/generated files on standard error\n"

    "   --version (-v):\n"
    "           display " << program_name << "'s version and terminate\n"

    "   --verbose:\n"
    "           generate verbose description of the analyzed grammar\n" <<
    endl;
}

