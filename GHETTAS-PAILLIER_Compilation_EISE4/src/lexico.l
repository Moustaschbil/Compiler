%{
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>
#include "defs.h"
#include "common.h"
#include "passe.h"

#include "y.tab.h"

void yyerror(char *);
int yyparse(void);
int fileno(FILE * stream);
void analyse_tree(node_t root);

char * infile = NULL;
char * outfile = "out.s";
bool stop_after_syntax = false;
bool stop_after_verif = false;

int nb_reg = DEFAULT_MAX_REGS;
int trace_level = DEFAULT_TRACE_LEVEL;
int yylex_destroy(void);
/* A completer */

#if YYDEBUG
extern int yydebug;
#endif


%}

%option yylineno


LETTRE          [a-zA-Z]
/* A compléter ; fausses définitions pour que lex ne fasse pas d'erreur */
CHIFFRE         [0-9]
IDF             {LETTRE}({LETTRE}|{CHIFFRE}|"_")*
CHIFFRE_NON_NUL [1-9]
ENTIER_DEC      "0"|{CHIFFRE_NON_NUL}{CHIFFRE}*
LETTRE_HEXA     [a-fA-F]
ENTIER_HEXA     "0x"({CHIFFRE}|{LETTRE_HEXA})+
SIGNE           "-"|""
ENTIER          {SIGNE}({ENTIER_DEC}|{ENTIER_HEXA})
CHAINE_CAR      [\ -!#-\[\]-~]
CHAINE          \"({CHAINE_CAR}|\\\"|\\n)*\"
COMMENTAIRE     //({CHAINE}|"")

%%

"void"          return TOK_VOID;
"int"		return TOK_INT;
"bool"		return TOK_BOOL;
"true"          return TOK_TRUE;
"false"         return TOK_FALSE;
"if"            return TOK_IF;
"else"          return TOK_ELSE;
"while"         return TOK_WHILE;
"do"            return TOK_DO;
"for"           return TOK_FOR;
"print"		return TOK_PRINT;
"+"		return TOK_PLUS;
"-"		return TOK_MINUS;
"/"		return TOK_DIV;
"*"		return TOK_MUL;
"%"		return TOK_MOD;
"="		return TOK_AFFECT;
"=="		return TOK_EQ;
"!="		return TOK_NE;
"<"		return TOK_LT;
"<="		return TOK_LE;
"<<"		return TOK_SLL;
">"		return TOK_GT;
">="		return TOK_GE;
">>"		return TOK_SRA;
">>>"		return TOK_SRL;
"!"		return TOK_NOT;
"~"		return TOK_BNOT;
"&"		return TOK_BAND;
"&&"		return TOK_AND;
"|"		return TOK_BOR;
"||"		return TOK_OR;
"^"		return TOK_BXOR;
";"		return TOK_SEMICOL;
","		return TOK_COMMA;
"("		return TOK_LPAR;
")"		return TOK_RPAR;
"{"		return TOK_LACC;
"}"		return TOK_RACC;

{IDF} {
                yylval.strval = strdup(yytext);
                return TOK_IDENT;
}

{ENTIER} {
                /* A compléter : affecter yylval.intval et faire des vérifications */
                yylval.intval = atoi(yytext);
                return TOK_INTVAL;
}

{CHAINE} {
                /* A completer : affecter yylval.strval */
                yylval.strval = strdup(yytext);
                return TOK_STRING;
}

[ \t\n]+

. {
                fprintf(stderr, "Error line %d: Lexical error\n", yylineno);
                exit(1);
}


%%

int yywrap(void) {
    return 1;
}

int main(int argc, char ** argv) {
    /* A completer */
    infile = argv[optind];
    node_t program_root = malloc(sizeof(node_t));
    if(!program_root){
        printf("Pas de malloc\n");
        return 0;
    }
    parse_args(argc, argv);
    #if YYDEBUG
    yydebug = 1;
    #endif

    /*yyin = fopen(infile, "r");*/
    if ((yyin = fopen(argv[optind], "r")) == NULL) {
            fprintf(stderr,"Error: input file '%s' does not exist.\n", argv[optind]);
            exit(1);
    }
    yyparse();
    /*dump_tree(program_root, "out.dot");*/
    fclose(yyin);
    analyse_tree(program_root);
    yylex_destroy();
    return 0;
}
