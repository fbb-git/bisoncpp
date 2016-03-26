#include "parser.ih"

size_t Parser::s_nHidden;

ostringstream Parser::s_hiddenName;

char Parser::s_semanticValue[] = "d_val__";   
                                    // name of the semantic value variable
                                    // used by the generated parser.
char Parser::s_semanticValueStack[] = "d_vsp__";  
                                    // name of the semantic value stack
                                    // used by the generated parser
char Parser::s_locationValueStack[] = "d_lsp__";  
                                    // name of the location value stack
                                    // used by the generated parser
char Parser::s_locationValue[] = "d_loc__";  
                                    // name of the location value variable
                                    // used by the generated parser (@0)

char const Parser::s_stype__[] = "STYPE__";
                                    // generic semantic value for POLYMORPHIC

string const Parser::s_undefined{"<undefined>"};


bool (Parser::*Parser::s_single[])(int nElements, Block &block, 
                                                    AtDollar const &atd) = 
{
//       loc,      // AA,      @@
//       locEl,    // An,      @nr
//
//       dval,     // DD,      $$
//       vsp,      // Dn,      $nr
//       vsp,      // D_,      $-nr
//
//       dval,     // refDD,   ($$)
//       vsp,      // refDn,   ($nr)
//       vsp,      // refD_,   ($-nr)
//
//       dvalMem,  // DDm, 	$$.
//       vspMem,   // Dnm,     $nr.
//       vspMem,   // D_m,     $-nr.
//
//       dvalPtr,  // DDp, 	$$->
//       vspPtr,   // Dnp,     $nr->
//       vspPtr,   // D_p,     $-nr->
//
//       err,      // refDt_   ($<TAG>-nr)
//       err,      // Dt_m,    $<TAG>-nr.
//       err,      // Dt_p     $<TAG>-nr->
};

bool (Parser::*Parser::s_union[])(int nElements, Block &block, 
                                    AtDollar const &atd) = 
{
//    loc,        loc,        // AA,      @@
//    locEl,      locEl,      // An,      @nr
//
//    dval,       dvalTag,    // DD,      $$
//    vsp,        vspTag,     // Dn,      $nr
//    vsp,        err,     vsp// D_,      $-nr
//
//    dval,       dval,       // refDD,   ($$)
//    vsp,        vsp,        // refDn,   ($nr)
//    vsp,        vsp,        // refD_,   ($-nr)
//
//    dvalMem,    dvalTagMem, // DDm, 	$$.
//    vspMem,     vspTagMem,  // Dnm,     $nr.
//    vspMem,     err,        // D_m,     $-nr.
//
//    dvalPtr,    dvalTagPtr, // DDp, 	$$->
//    vspPtr,     vspTagPtr,  // Dnp,     $nr->
//    vspPtr,     err,        // D_p,     $-nr->
//
//    err,        err,        // refDt_   ($<TAG>-nr)
//    err,        err,        // Dt_m,    $<TAG>-nr.
//    err,        err,        // Dt_p     $<TAG>-nr->
};

bool (Parser::*Parser::s_polymorphic[])(int nElements, Block &block, 
                                                AtDollar const &atd) =  
{
      &Parser::loc,        // AA,      @@
      &Parser::locEl,      // An,      @nr

      &Parser::dval,       // DD,      $$
      &Parser::vsp,        // Dn,      $nr
      &Parser::vsp,        // D_,      $-nr

      &Parser::dvalRef,    // refDD,   ($$)
      &Parser::vspRef,     // refDn,   ($nr)
      &Parser::errNegative,// refD_,   ($-nr)

      &Parser::dvalMem,    // DDm, 	  $$.
      &Parser::vspMem,     // Dnm,     $nr.
      &Parser::errNegative,// D_m,     $-nr.

      &Parser::dvalPtr,    // DDp, 	  $$->
      &Parser::vspPtr,     // Dnp,     $nr->
      &Parser::errNegative,// D_p,     $-nr->

      &Parser::vspTagRef,  // refDt_   ($<TAG>-nr)
      &Parser::vspTagMem,  // Dt_m,    $<TAG>-nr.
      &Parser::vspTagPtr,  // Dt_p     $<TAG>-nr->
};









