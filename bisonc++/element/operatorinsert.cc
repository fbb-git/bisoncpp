#include "element.ih"

ostream &operator<<(ostream &out, Element const *element)
{
    return element->insert(out);
}    
