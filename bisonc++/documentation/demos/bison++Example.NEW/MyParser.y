%class-name MyParser
%scanner MyScanner.h
%lsp-needed
%lines

%union {
  int num;
  bool statement;
  }

%token INTEGER
%token BOOLEAN

%type <num> exp result integer
%type <statement> bexp boolean

%start result

%left OR
%left AND
%left PLUS MINUS
%left NOT
%left LPARA RPARA

%%

result: exp {cout << "Result = " << $1 << endl;}
                | bexp {cout << "Result = " << $1 << endl;}

exp     : exp PLUS exp {$$ = $1 + $3;}
            | integer {$$ = $1;}
                | MINUS exp { $$ = -$2;}
                | exp MINUS exp {$$ = $1 - $3;}

bexp            : boolean {$$ = $1;}
        | bexp AND bexp { $$ = $1 && $3;}
        | bexp OR bexp { $$ = $1 || $3;}
        | NOT bexp {$$ = !$2;}
        | LPARA bexp RPARA {$$ = $2;}

integer:    
    INTEGER
    {
        $$ = atoi(d_scanner.YYText());
    }

boolean:
    BOOLEAN
    {
        $$ = string("TRUE") == d_scanner.YYText();
    }
