/*
                              demo.cc
*/

#include "main.ih"

int main(int argc, char **argv)
{
    if (isatty(STDIN_FILENO))
    {
        cout << "Run the program as `demo < input'\n"
            "Use any program argument to view parser's debug output\n";
    }

    Parser parser;

    parser.setDebug(argc > 1);

    cout << "When input-redirecting `input' (e.g., `demo < input') the output"
                                                            " should be:\n"
        "        Mid-rule: s-type, j\n"
        "        s-type j scoped\n"
        "\n";

    int ret = parser.parse();

    cout << "\n"
            "Parser returns " << ret << endl;

    return 0;
}




