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
       &Parser::loc,            // AA,      @@
       &Parser::locEl,          // An,      @nr
                                
       &Parser::dval,           // DD,      $$
       &Parser::svs,            // Dn,      $nr
       &Parser::svs,            // D_,      $-nr
                                
       &Parser::errNoRef,       // refDD,   _$$
       &Parser::errNoRef,       // refDn,   _$nr
       &Parser::errNoRef,       // refD_,   _$-nr
                                
       &Parser::dvalDirectMem,  // DDm,     $$.
       &Parser::svsDirectMem,   // Dnm,     $nr.
       &Parser::svsDirectMem,   // D_m,     $-nr.
                                
       &Parser::dvalDirectPtr,  // DDp,     $$->
       &Parser::svsDirectPtr,   // Dnp,     $nr->
       &Parser::svsDirectPtr,   // D_p,     $-nr->
                                
       &Parser::errNoRef,       // refDt_   _$<TAG>-nr
       &Parser::errNoTag,       // Dt_m,    $<TAG>-nr.
       &Parser::errNoTag,       // Dt_p     $<TAG>-nr->
};

bool (Parser::*Parser::s_union[])(int nElements, Block &block, 
                                    AtDollar const &atd) = 
{
//    loc,        loc,        // AA,      @@
//    locEl,      locEl,      // An,      @nr
//
//    dval,       dvalTag,    // DD,      $$
//    svs,        svsTag,     // Dn,      $nr
//    svs,        err,     svs// D_,      $-nr
//
//    dval,       dval,       // refDD,   ($$)
//    svs,        svs,        // refDn,   ($nr)
//    svs,        svs,        // refD_,   ($-nr)
//
//    dvalMem,    dvalTagMem, // DDm,   $$.
//    svsMem,     svsTagMem,  // Dnm,     $nr.
//    svsMem,     err,        // D_m,     $-nr.
//
//    dvalPtr,    dvalTagPtr, // DDp,   $$->
//    svsPtr,     svsTagPtr,  // Dnp,     $nr->
//    svsPtr,     err,        // D_p,     $-nr->
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
      &Parser::svs,        // Dn,      $nr
      &Parser::svs,        // D_,      $-nr

      &Parser::dvalRef,    // refDD,   _$$
      &Parser::svsRef,     // refDn,   _$nr
      &Parser::errNegative,// refD_,   _$-nr

      &Parser::dvalMem,    // DDm,     $$.
      &Parser::svsMem,     // Dnm,     $nr.
      &Parser::errNegative,// D_m,     $-nr.

      &Parser::dvalPtr,    // DDp,     $$->
      &Parser::svsPtr,     // Dnp,     $nr->
      &Parser::errNegative,// D_p,     $-nr->

      &Parser::svsTagRef,  // refDt_   _$<TAG>-nr
      &Parser::svsTagMem,  // Dt_m,    $<TAG>-nr.
      &Parser::svsTagPtr,  // Dt_p     $<TAG>-nr->
};









