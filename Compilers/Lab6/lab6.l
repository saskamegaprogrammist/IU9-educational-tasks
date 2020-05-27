%option noyywrap bison-bridge bison-locations

%{

# include <stdio.h>
# include <stdlib.h>
# define TAG_REGEXP 1
# define TAG_STRING 2

char *tag_names[] = {
        "REGEXP", "STRING"
};

struct Position {
    int line , pos , index;
};

void print_pos (struct Position *p) {
    printf ("(%d ,%d)", p->line, p->pos);
}

struct Fragment {
    struct Position starting, following;
};

typedef struct Fragment YYLTYPE;

void print_frag (struct Fragment *f) {
    print_pos (&(f->starting));
    printf ("-");
    print_pos (&(f->following));
}

union Token {
    char* string;
    char* regexp
};

typedef union Token YYSTYPE;

int continued;
struct Position cur;
int yy_flex_debug;

char* curr_string;
int max_size = 100;
int curr_string_size;

void alloc_string() {
    curr_string = (char*)malloc((max_size+1)*sizeof(char));
    curr_string[0] = '\0';
}

void free_string() {
    free(curr_string);
}


# define YY_USER_ACTION {            \
    if (!continued)   {               \
        free_string();               \
        alloc_string();              \
        yylloc -> starting = cur;    \
    }                                \
    if (yytext[0] == '\n') {         \
       cur.line++;                   \
       cur.pos = 1;                  \
    } else {                         \
        cur.pos+= yyleng;            \
        strcat(curr_string, yytext); \
    }                                \
    cur.index+= yyleng;              \
    continued = 0;                   \
    yylloc -> following = cur ;      \
}

void init_scanner () {
    continued = 0;
    cur.line = 1;
    cur.pos = 1;
    cur.index = 0;
    alloc_string();
}

void close_scanner() {
    free_string();
}

void err(const char* msg) {
    printf(" Error ");
    print_pos(&cur);
    printf(": %s\n", msg);
}

%}


%x REGEXP STRING

%%

[\t ]+
\n
\/                      {
                            continued = 1;
                            BEGIN(REGEXP);
                        }
<REGEXP>[^(\\n|\\\/|\\\\|\n|\/)]*        continued = 1;
<REGEXP>\\n|\\\/|\\\\   continued = 1;
<REGEXP>\n              {
                            err("newline in regexp");
                            continued=1;
                        }

<REGEXP>\/             {
                            yylval->regexp = curr_string;
                            BEGIN(0);
                            return TAG_REGEXP;
                        }
<REGEXP><<EOF>>        {
                            err("EOF found, '/' expected");
                            return 0;
                        }
\"\"\"                  {
                            continued = 1;
                            BEGIN(STRING);

                       }
<STRING>\"\"\"         {
                            yylval->string = curr_string;
                            BEGIN(0);
                            return TAG_STRING;
                        }
<STRING>[^\"\n]*        continued = 1;
<STRING>\"            continued = 1;
<STRING>\n            continued = 1;
<STRING>\"\"          continued = 1;
<STRING><<EOF>>        {
                            err("EOF found, '\"\"\"' expected");
                            return 0;
                        }
%%

int main(int argc, const char *argv[]) {
    FILE *f;
    if (argc > 1) {
        f = fopen(argv[1], "r");
        if (!f) {
            perror(argv[1]);
            return 1;
        } else {
            yyin = f;
        }

    }
    yy_flex_debug = 1;
    YYSTYPE value;
    YYLTYPE coords;
    int tag;
    init_scanner();
    for (;;) {
        tag = yylex(&value, &coords);
        if (tag == 0) {
            close_scanner();
            break;
        }
        else {
            print_frag(&coords);
            if (tag == TAG_REGEXP) {
                printf(": REGEXP %s\n", (&value)->regexp);
            } else {
                printf(": STRING %s\n", (&value)->string);
            }
        }
    }
    fclose(f);
    return 0;
}
