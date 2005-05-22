#ifndef _INCLUDED_ELEMENT_
#define _INCLUDED_ELEMENT_

#include <ostream>
#include <string>

    // Placeholder in FirstSet for Symbols, to prevent circular class 
    // dependencies
class Element
{
    public:
        struct SDContext
        {
            std::ostream &out;
            char const *sep;
        };

        virtual ~Element();

        virtual std::ostream &insert(std::ostream &out) const
        {
            return out;
        }
        virtual std::string const &display() const = 0;

        static void sDisplay(Element const *element, SDContext &context)
        {
            context.out << element->display() << context.sep;
        }
    private:
};

std::ostream &operator<<(std::ostream &out, Element const *el);
        
#endif
