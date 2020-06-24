%option noyywrap c++ yylineno

%{
#include "Parserbase.h"
%}

DIGIT   [0-9]
WS  [ \t\n]

%%

{DIGIT}*                    return Parser::NUMBER;
[a-z][a-z0-9_]*             return Parser::VAR_NAME;
I                           return Parser::INT;
B                           return Parser::BOOL;

PROGRAM                     return Parser::PROGRAM;
DATA                        return Parser::DATA;
TYPE                        return Parser::TYPE;

WHILE                       return Parser::WHILE;
ENDWHILE                    return Parser::ENDWHILE;
IF                          return Parser::IF;
ELSE                        return Parser::ELSE;
ENDIF                       return Parser::ENDIF;

MOVE                        return Parser::MOVE;
READ                        return Parser::READ;
WRITE                       return Parser::WRITE;
TO                          return Parser::TO;
FROM                        return Parser::FROM;
BY                          return Parser::BY;

ADD                         return Parser::ADD;
SUBTRACT                    return Parser::SUBTRACT;
MULTIPLY                    return Parser::MULTIPLY;
DIVIDE                      return Parser::DIVIDE;
MOD                         return Parser::MOD;
OR                          return Parser::OR;
AND                         return Parser::AND;
NOT                         return Parser::NOT;
"="                         return Parser::EQUALS;
"<"                         return Parser::LESS_THAN;
">"                         return Parser::MORE_THAN;

TRUE                        return Parser::TRUE;
FALSE                       return Parser::FALSE;

":"                         return Parser::COLON;
"."                         return Parser::DOT;
","                         return Parser::COMMA;
"("                         return Parser::OPENING_BRACKET;
")"                         return Parser::CLOSING_BRACKET;

^"*".*                      // csillagnal semmi, csak megjegyzes
{WS}+                       // feher szokozok: semmi teendo

.           {
                std::cerr << lineno() << ": Lexikalis hiba." << std::endl;
                exit(1);
            }

%%
