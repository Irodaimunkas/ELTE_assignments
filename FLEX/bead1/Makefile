abap: abap.cc lex.yy.cc
	g++ -oabap abap.cc lex.yy.cc

lex.yy.cc: abap.l
	flex abap.l

clean:
	rm -f lex.yy.cc abap
