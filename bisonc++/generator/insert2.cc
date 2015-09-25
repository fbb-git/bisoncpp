#include "generator.ih"

void Generator::insert(ostream &out, size_t indent, char const *skel) const
{
    ifstream in;
    Exception::open(in, d_options.skeletonDirectory() + skel);

    Indent::setWidth(indent);

    string line;
    bool accept = true;

    while (getline(in, line))
    {
        if (line.find('@') == 0)        // @ immediately at BOL
            bolAt(out, line, in, accept);
        else if (accept)
        {
            replaceBaseFlag(line);
            out << FBB::indent << line << '\n';
        }
    }
}








