#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char **argv)
{
    string label(argv[1]);
    string endlabel(label[1] == '/' ? "//=" : "/**/");
    ifstream input(argv[2]);

    string line;
    bool print = false;

    cout << "        verb(\n";
    while (getline(input, line))
    {
        if (line.find(label) == 0)
        {
            if (print)
                break;
            print = true;
            label = endlabel;
            continue;
        }
        if (print)
            cout << line << endl;
    }
    cout << "        )\n";
    if (!print)
    {
        cerr << "verbinsert(" << argv[1] << ")(" << argv[2] << ")\n" <<
                "          label section not found\n";
        return 1;
    }
    if (label != endlabel)
    {
        cerr << "verbinsert(" << argv[1] << ")(" << argv[2] << ")\n" <<
                "          unterminated label section\n";
        return 1;
    }
    return 0;
}
