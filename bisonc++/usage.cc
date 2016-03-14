#include "main.ih"

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

    "   --analyze-only (-A): only analyze the grammar; except for possibly\n"
    "           the verbose grammar description file no files are written.\n"

    "   --baseclass-preinclude=<header> (-H):\n"
    "           preinclude header in the base-class header file.\n"
    "           Use [header] to include <header>, otherwise \"header\"\n"
    "           will be included.\n"

    "   --baseclass-header=<header> (-b):\n"
    "           filename holding the base class definition.\n"

    "   --baseclass-skeleton=<skeleton> (-B):\n"
    "           location of the baseclass header skeleton.\n"

    "   --class-header=<header> (-c):\n"
    "           filename holding the parser class definition.\n"

    "   --class-skeleton=<skeleton> (-C):\n"
    "           location of the class header skeleton.\n"

    "   --construction: write details about the grammar analysis to stdout.\n"

    "   --debug: generates debug output statements in the generated parse\n"
    "           function's source.\n"

    "   --error-verbose: the parse function will dump the parser's state\n"
    "           stack to stdout when a syntactic error is reported\n"

    "   --filenames=<filename> (-f):\n"
    "           filename of output files (overruling the default filename).\n"

    "   --help (-h): produce this information (and terminate).\n"

    "   --implementation-header=<header> (-i):\n"
    "           filename holding the implementation header.\n"

    "   --implementation-skeleton=<skeleton> (-I):\n"
    "           location of the implementation header skeleton.\n"

    "   --include-only: catenate all grammar files in their order of\n"
    "           processing to the standard output stream and terminate.\n"

    "   --insert-stype: show selected semantic values in the output "
                                                                "generated\n"
    "           by --debug. Ignored unless --debug was specified.\n"

    "   --max-inclusion-depth=<value>:\n"
    "           sets the maximum number of nested grammar files (default: "
                                                                    "10).\n"
    "   --namespace=<namespace> (-n):\n"
    "           define the parser in the mentioned namespace.\n"

    "   --no-baseclass-header: don't create the parser's base class header.\n"

    "   --no-decoration (-D): do not include the user-defined actions when\n"
    "           generating the parser's tt(parse) member.\n"

    "   --no-default-action (-N): do not use the default $$ = $1 assignment\n"
    "           of semantic values when returning from an action block\n"

    "   --no-default-constructors: do not check whether default "
                                                            "constructors\n"
    "           are available for polymorphic semantic value types\n"

    "   --no-lines: don't put #line directives in generated output,\n"
    "           overruling the %lines directive.\n"

    "   --no-parse-member: don't create the member parse().\n"

    "   --own-debug:\n"
    "           bisonc++ displays the actions of its parser while "
                                                                "processing\n"
    "           its input file(s) (implies --verbose).\n"

    "   --own-tokens (-t):\n"
    "           bisonc++ displays the tokens and their corresponding\n"
    "           matched text it received from its lexcial scanner.\n"

    "   --parser-skeleton=<parserskel> (-P):\n"
    "           location of the parse function's skeleton.\n"

    "   --parsefun-source=<source> (-p):\n"
    "           filename holding the parse function's source.\n"

    "   --polymorphic-code-skeleton=<skeleton> (-L):\n"
    "           location of the non-inline polymorphic functions skeleton.\n"

    "   --polymorphic-skeleton=<skeleton> (-M):\n"
    "           location of the polymorphic semantic values skeleton.\n"

    "   --print-tokens (-t):\n"
    "           the print() member of the generated parser class displays\n"
    "           the tokens and their corresponding matched text.\n"

    "   --required-tokens=<value>:\n"
    "           minimum number of successfully processed tokens between\n"
    "           errors (default: 0).\n"

    "   --scanner=<header-file> (-s):\n"
    "           include `header-file' declaring the class Scanner, and call\n"
    "           d_scanner.yylex() from Parser::lex().\n"

    "   --scanner-class-name=<scanner class name>:\n"
    "           specifies the name of the scanner class: this option is\n"
    "           only interpreted if --scanner (or %scanner) is also used.\n"

    "   --scanner-debug: extensive display of the actions of bisonc++'s "
                                                                "scanner\n"

    "   --scanner-token-function=<scanner token function>:\n"
    "           define the function called from lex() returning the next\n"
    "           token returned (by default d_scanner.yylex() when --scanner\n"
    "           is used)\n"

    "   --show-filenames: show the names of the used/generated files on\n"
    "           the standard error stream.\n"

    "   --skeleton-directory=<skeleton-directory> (-S):\n"
    "           location of the skeleton directory.\n"

    "   --thread-safe: no static data are modified, making bisonc++'s\n"
    "           generated code thread-safe.\n"

    "   --usage: produce this information (and terminate).\n"

    "   --verbose (-V):\n"
    "           generate verbose description of the analyzed grammar.\n" 

    "   --version (-v):\n"
    "           display " << program_name << "'s version and terminate.\n"

                                                                    << endl;
}

