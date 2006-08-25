#ifndef _INCLUDED_ELEMENT_
#define _INCLUDED_ELEMENT_

#include <ostream>
#include <string>

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
    //
class Element
{
    public:
        virtual ~Element();

        virtual std::string const &display() const = 0;
        virtual std::string const &literal() const
        {
            return display();
        }
        virtual size_t/*unsigned*/ value() const = 0;
};

std::ostream &operator<<(std::ostream &out, Element const *el);
        
#endif
