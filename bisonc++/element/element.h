#ifndef _INCLUDED_ELEMENT_
#define _INCLUDED_ELEMENT_

#include <ostream>
#include <string>

#include "../om/om.h"

    // Placeholder in FirstSet for Symbols, to prevent circular class 
    // dependencies
    //
    // Also defines basic display functionality:
    // Display-forms of symbols:
    //  Symbol Type             operator<<  literal()  value()
    //                          display()
    //  ------------------------------------------------------------------
    //  Terminal (printable)    'x'         'x'         123 
    //                                      (if so provided)
    //  Terminal (nonprintable) '\xdd'      '\xdd'      123
    //                                      (if so provided)
    //  Terminal (Symbolic)     `NAME'      NAME        281
    //  NonTerm                 `name'      name        12
    //  ------------------------------------------------------------------
    // original
    // Terminal::insert inserts the symbol followed by (= value)


class Element
{
    friend std::ostream &operator<<(std::ostream &out, Element const *el);

    public:
        virtual ~Element();
        virtual size_t value() const = 0;

    protected:
        virtual std::ostream &insert(std::ostream &out) const = 0;
};

inline std::ostream &operator<<(std::ostream &out, Element const *element)
{
    return element->insert(out) << OM::reset;
}
        
#endif
