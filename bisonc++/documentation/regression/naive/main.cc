#include "main.ih"

int main()
{
    cout << "Enter numbers separated by semicolons\n";

    Parser parser;
    return parser.parse();
}
