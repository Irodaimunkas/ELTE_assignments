%option noyywrap c++ yylineno

%{
#include <iostream>
#include <cstdlib>
%}

DIGIT   [0-9]
WS  [ \t\n]

%%

{DIGIT}*                    std::cout << "NUMBER" << std::endl;
[a-z][a-z{DIGIT}_]*         std::cout << "identifier: " << YYText() << std::endl;
I                           std::cout << "type: INTEGER" << std::endl;
B                           std::cout << "type: BOOLEAN" << std::endl;

PROGRAM                     std::cout << "PROGRAM" << std::endl;
DATA                        std::cout << "DATA" << std::endl;
TYPE                        std::cout << "TYPE" << std::endl;

WHILE                       std::cout << "WHILE" << std::endl;
ENDWHILE                    std::cout << "ENDWHILE" << std::endl;
IF                          std::cout << "IF" << std::endl;
ELSE                        std::cout << "ELSE" << std::endl;
ENDIF                       std::cout << "ENDIF" << std::endl;

MOVE                        std::cout << "MOVE" << std::endl;
READ                        std::cout << "READ" << std::endl;
WRITE                       std::cout << "WRITE" << std::endl;
TO                          std::cout << "TO" << std::endl;
FROM                        std::cout << "FROM" << std::endl;
BY                          std::cout << "BY" << std::endl;

ADD                         std::cout << "ADD" << std::endl;
SUBTRACT                    std::cout << "SUBTRACT" << std::endl;
MULTIPLY                    std::cout << "MULTIPLY" << std::endl;
DIVIDE                      std::cout << "DIVIDE" << std::endl;
MOD                         std::cout << "MOD" << std::endl;
OR                          std::cout << "OR" << std::endl;
AND                         std::cout << "AND" << std::endl;
NOT                         std::cout << "NOT" << std::endl;
"="                         std::cout << "EQUALS" << std::endl;
"<"                         std::cout << "LESS THAN" << std::endl;
">"                         std::cout << "GREATER THAN" << std::endl;

TRUE                        std::cout << "TRUE" << std::endl;
FALSE                       std::cout << "FALSE" << std::endl;

":"                         // semmi
"."                         // pontnal semmi teendo
","                         // vessző csak elvalasztas
^"*".*                      // csillagnal semmi, csak megjegyzes
{WS}+                       // feher szokozok: semmi teendo

.           {
                std::cerr << lineno() << ": Lexikalis hiba." << std::endl;
                exit(1);
            }

%%
