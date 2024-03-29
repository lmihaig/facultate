%{
#include <stdio.h>
#include <string.h>

void print_token(const char* token_type, const char* token, int line_number) {
    printf("%s:\t%s\tLINE:%d\n", token_type, token, line_number);
}

%}

%option noyywrap
%option yylineno

KEYWORDS           (as|async|await|break|const|continue|crate|dyn|else|enum|extern|false|fn|for|if|impl|in|let|loop|match|mod|move|mut|pub|ref|return|Self|self|static|struct|super|trait|true|type|unsafe|use|where|while|try|union)
NEWLINES           ((\r\n)|\n|\t|\x0B|\x0C|\x20|\x85|\xE2\x80\x8E|\xE2\x80\x8F|\xE2\x80\xA8|\xE2\x80\xA9)
COMMENTS           (\/\/.*|\/\*([^*]|\*+[^*/])*\*+\/)
IDENTIFIER         [a-zA-Z_][a-zA-Z0-9_]*
OPERATORS          ([+\-*/=<>!%^&|]+)
DELIMITERS         ([(),.{};:])
RAW_LITERAL        r#"[^"]*"#|r#"'[^']*'#
BYTE_LITERAL       b?'[^']*'|b?\"[^\"]*\"
C_LITERAL          c?\"[^"]*\"|c?\'[^\']*\'
STRING_LITERAL     \"(\\.|[^"\\])*\"|'(\\.|[^'\\])*'
NUMERIC_LITERAL    [0-9]+(\.[0-9]*)?|\.[0-9]+|[0-9]+[eE][+\-]?[0-9]+|0[xX][0-9a-fA-F]+
LIFETIME_LITERAL   '[a-zA-Z_][a-zA-Z0-9_]*
LITERALS      {RAW_LITERAL}|{BYTE_LITERAL}|{C_LITERAL}|{STRING_LITERAL}|{NUMERIC_LITERAL}|{LIFETIME_LITERAL}

%%

{COMMENTS}    { print_token("COMMENT", yytext, yylineno); }
[ \t]         {/*ignore whitespace*/}
{KEYWORDS}    { print_token("KEYWORD", yytext, yylineno); }
{IDENTIFIER}  { print_token("IDENTIFIER", yytext, yylineno); }
{LITERALS}    { print_token("LITERAL", yytext, yylineno); }
{OPERATORS}   { print_token("OPERATOR", yytext, yylineno); }
{DELIMITERS}  { print_token("DELIMITER", yytext, yylineno); }
{NEWLINES}    { /* increment yylineno */ }
.             { fprintf(stderr, "Invalid lexical character: %s at line %d\n", yytext, yylineno); }
%%

int main() {
    yylex();
    return 0;
}
