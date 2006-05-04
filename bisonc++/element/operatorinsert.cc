#include "element.ih"

ostream &operator<<(ostream &out, Element const *element)
{
    return out << element->display();
}    
