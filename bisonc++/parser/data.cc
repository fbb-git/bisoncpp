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


Parser::ADmap Parser::s_single =
{
       {AtDollar::AA, &Parser::loc},            // @@
       {AtDollar::An, &Parser::locEl},          // @nr
                                
       {AtDollar::DD, &Parser::dval},           // $$
       {AtDollar::Dn, &Parser::svs},            // $nr
       {AtDollar::D_, &Parser::svs},            // $-nr
                                
//       {AtDollar::refDD, &Parser::errNoRef},       // _$$
//       {AtDollar::refDn, &Parser::errNoRef},       // _$nr
//       {AtDollar::refD_, &Parser::errNoRef},       // _$-nr
                                
       {AtDollar::DDm, &Parser::dvalDirectMem},  // $$.
       {AtDollar::Dnm, &Parser::svsDirectMem},   // $nr.
       {AtDollar::D_m, &Parser::svsDirectMem},   // $-nr.
                                
       {AtDollar::DDp, &Parser::dvalDirectPtr},  // $$->
       {AtDollar::Dnp, &Parser::svsDirectPtr},   // $nr->
       {AtDollar::D_p, &Parser::svsDirectPtr},   // $-nr->
                                
//       {AtDollar::refDt_, &Parser::errNoRef},       // _$<TAG>-nr
       {AtDollar::Dt_m, &Parser::errNoTag},       // $<TAG>-nr.
       {AtDollar::Dt_p, &Parser::errNoTag},       // $<TAG>-nr->
};

Parser::ADmap Parser::s_union =
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

Parser::ADmap Parser::s_polymorphic =
{
      {AtDollar::AA, &Parser::loc},        	    // @@
      {AtDollar::An, &Parser::locEl},      	    // @nr
                           	    
      {AtDollar::DD, &Parser::dval},       	    // $$
      {AtDollar::Dn, &Parser::svs},        	    // $nr
      {AtDollar::D_, &Parser::svs},        	    // $-nr
                           	    
//      {AtDollar::refDD, &Parser::dvalRef},    	    // _$$
//      {AtDollar::refDn, &Parser::svsRef},     	    // _$nr
//      {AtDollar::refD_, &Parser::errNegative},	    // _$-nr
                           	    
      {AtDollar::DDm, &Parser::dvalMem},    	    // $$.
      {AtDollar::Dnm, &Parser::svsMem},     	    // $nr.
      {AtDollar::D_m, &Parser::errNegative},	    // $-nr.
                           	    
      {AtDollar::DDp, &Parser::dvalPtr},    	    // $$->
      {AtDollar::Dnp, &Parser::svsPtr},     	    // $nr->
      {AtDollar::D_p, &Parser::errNegative},	    // $-nr->
                           	    
//      {AtDollar::refDt_, &Parser::svsTagRef},  	    // _$<TAG>-nr
      {AtDollar::Dt_m, &Parser::svsTagMem},  	    // $<TAG>-nr.
      {AtDollar::Dt_p, &Parser::svsTagPtr},  	    // $<TAG>-nr->
};









