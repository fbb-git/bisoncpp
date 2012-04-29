#include "generator.ih"

void Generator::insert(ostream &out) const
{
    istringstream istr(d_line);
    istr >> d_key >> d_indent;

    if (!istr)
    {
        d_indent = 0;
        istr.clear();
    }
    istr >> d_key;     // extract the insertion target

    getline(istr, d_line);      // and store the remainder of the line

    MapConstIter iter = s_insert.find(d_key);

    if (iter != s_insert.end())
        (this->*iter->second)(out);
    else
        wmsg << "Ignoring unsupported `$insert " << d_key << 
                " ...' in skeleton file" << endl;
}





