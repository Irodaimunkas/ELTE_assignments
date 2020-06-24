%baseclass-preinclude <iostream>
%lsp-needed

%token NUMBER VAR_NAME INT BOOL
%token PROGRAM DATA TYPE
%token WHILE ENDWHILE IF ELSE ENDIF
%token MOVE READ WRITE TO FROM BY

%left ADD SUBTRACT MULTIPLY DIVIDE MOD OR AND NOT EQUALS LESS_THAN MORE_THAN

%token TRUE FALSE
%token COLON DOT COMMA OPENING_BRACKET CLOSING_BRACKET

%%

start:
    PROGRAM VAR_NAME DOT
    {
        std::cout << "start -> PROGRAM VAR_NAME DOT" << std::endl;
    }
|
    PROGRAM VAR_NAME DOT DATA COLON declare expressions
    {
        std::cout << "start -> PROGRAM VAR_NAME DOT DATA COLON declare expressions" << std::endl;
    }
|
    PROGRAM VAR_NAME DOT DATA COLON declare
    {
        std::cout << "start -> PROGRAM VAR_NAME DOT DATA COLON declare" << std::endl;
    }
|
    PROGRAM VAR_NAME DOT expressions
    {
        std::cout << "start -> PROGRAM VAR_NAME DOT expressions" << std::endl;
    }
;

declare:
    VAR_NAME TYPE INT COMMA declare
    {
        std::cout << "declare -> VAR_NAME TYPE INT COMMA declare" << std::endl;
    }
|
    VAR_NAME TYPE INT DOT
    {
        std::cout << "declare -> VAR_NAME TYPE INT DOT" << std::endl;
    }
|
    VAR_NAME TYPE BOOL COMMA declare
    {
        std::cout << "declare -> VAR_NAME TYPE BOOL COMMA declare" << std::endl;
    }
|
    VAR_NAME TYPE BOOL DOT
    {
        std::cout << "declare -> VAR_NAME TYPE BOOL DOT" << std::endl;
    }
;

expressions:
    exp expressions
    {
        std::cout << "expressions -> exp expressions" << std::endl;
    }
|
    exp
    {
        std::cout << "expressions -> exp" << std::endl;
    }
|
    MOVE exp TO VAR_NAME DOT expressions
    {
        std::cout << "expressions -> MOVE exp TO VAR_NAME DOT expressions" << std::endl;
    }
|
    MOVE exp TO VAR_NAME DOT
    {
        std::cout << "expressions -> MOVE exp TO VAR_NAME DOT" << std::endl;
    }
|
    READ TO VAR_NAME DOT expressions
    {
        std::cout << "expressions -> READ TO VAR_NAME DOT expressions" << std::endl;
    }
|
    READ TO VAR_NAME DOT
    {
        std::cout << "expressions -> READ TO VAR_NAME DOT" << std::endl;
    }
|
    WRITE exp DOT expressions
    {
        std::cout << "expressions -> WRITE exp DOT expressions" << std::endl;
    }
|
    WRITE exp DOT
    {
        std::cout << "expressions -> WRITE exp DOT" << std::endl;
    }
|
    WHILE exp DOT expressions ENDWHILE DOT expressions
    {
        std::cout << "expressions -> WHILE exp DOT expressions ENDWHILE DOT expressions" << std::endl;
    }
|
    WHILE exp DOT expressions ENDWHILE DOT
    {
        std::cout << "expressions -> WHILE exp DOT expressions ENDWHILE DOT" << std::endl;
    }
|
    IF exp DOT expressions ENDIF DOT expressions
    {
        std::cout << "expressions -> IF exp DOT expressions ENDIF expressions" << std::endl;
    }
|
    IF exp DOT expressions ENDIF DOT
    {
        std::cout << "expressions -> IF exp DOT expressions ENDIF" << std::endl;
    }
|
    IF exp DOT expressions ELSE DOT expressions ENDIF DOT expressions
    {
        std::cout << "expressions -> IF exp DOT expressions ELSE DOT expressions ENDIF expressions" << std::endl;
    }
|
    IF exp DOT expressions ELSE DOT expressions ENDIF DOT
    {
        std::cout << "expressions -> IF exp DOT expressions ELSE DOT expressions ENDIF" << std::endl;
    }
;

exp:
    NUMBER
    {
        std::cout << "exp -> NUMBER" << std::endl;
    }
|
    VAR_NAME
    {
        std::cout << "exp -> VAR_NAME" << std::endl;
    }
|
    TRUE
    {
        std::cout << "exp -> TRUE" << std::endl;
    }
|
    FALSE
    {
        std::cout << "exp -> FALSE" << std::endl;
    }
|
    ADD exp TO VAR_NAME DOT
    {
        std::cout << "exp -> ADD exp TO VAR_NAME DOT" << std::endl;
    }
|
    SUBTRACT exp FROM VAR_NAME DOT
    {
        std::cout << "exp -> SUBTRACT exp FROM VAR_NAME DOT" << std::endl;
    }
|
    MULTIPLY VAR_NAME BY exp DOT
    {
        std::cout << "exp -> MULTIPLY VAR_NAME BY exp DOT" << std::endl;
    }
|
    DIVIDE VAR_NAME BY exp DOT
    {
        std::cout << "exp -> DIVIDE VAR_NAME BY exp DOT" << std::endl;
    }
|
    MOD VAR_NAME BY exp TO VAR_NAME DOT
    {
        std::cout << "exp -> MOD VAR_NAME BY exp TO VAR_NAME DOT" << std::endl;
    }
|
    exp OR exp
    {
        std::cout << "exp -> exp OR exp" << std::endl;
    }
|
    exp AND exp
    {
        std::cout << "exp -> exp AND exp" << std::endl;
    }
|
    NOT exp
    {
        std::cout << "exp -> NOT exp" << std::endl;
    }
|
    exp EQUALS exp
    {
        std::cout << "exp -> exp EQUALS exp" << std::endl;
    }
|
    exp LESS_THAN exp
    {
        std::cout << "exp -> exp LESS_THAN exp" << std::endl;
    }
|
    exp MORE_THAN exp
    {
        std::cout << "exp -> exp MORE_THAN exp" << std::endl;
    }
|
    OPENING_BRACKET exp CLOSING_BRACKET
    {
        std::cout << "exp -> OPEN exp CLOSE" << std::endl;
    }
;
